/*
Copyright 2020,2021 LiGuer. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
	http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef MONTECARLO_TREE_SEARCH
#define MONTECARLO_TREE_SEARCH
#include <vector>
/******************************************************************************
*					Montecarlo Tree Search ���ؿ���������
*	[�㷨]:
		[1] selection,
		[2] expansion,
		[3] simulation,
		[4] backpropagation.
******************************************************************************/
template<class State>
class MonteCarloTreeSearch {
public:
	/*--------------------------------------------------------------------------------
						Montecarlo ���ڵ�
	*	[����]: [1]״̬		[2]ʤ������		[3]ʧ�ܴ���
				[4]���ڵ�	[5]�ӽڵ��б�	[6]�ӽڵ�������־
	*	[ע]: root����ʱ�������ӵ�������Ҳ���Զ������������ͷ��ڴ�.
	--------------------------------------------------------------------------------*/
	struct TreeNode {
		int rewardSum = 0, 
			visitTime = 0;
		State*    state  = NULL;
		TreeNode* parent = NULL;
		bool isChildFull = false;
		std::vector<TreeNode*> child;
		// ��������
		~TreeNode() {
			delete state;
			for (int i = 0; i < child.size(); i++)
				delete child[i];
		}
	};

	/*--------------------------------------------------------------------------------
						��������
	*	[����]: [1]���ڵ�		[2]�����������
				[3]���������״̬����ָ��	[4]�ж���Ӯ����ָ��
	--------------------------------------------------------------------------------*/
	TreeNode root;
	int  maxSearchTimes;
	bool(*newStateRandFunc)	(State&, State&, bool);			//���������״̬
	char(*judgeWin)	        (State&);						//�ж���Ӯ

	/*--------------------------------------------------------------------------------
						���캯��
	*	[����]: 
			[1]���������״̬����ָ��	(״̬, ��״̬, �Ƿ�ģ���־)
			[2]�ж���Ӯ����ָ��			(״̬)
	--------------------------------------------------------------------------------*/
	MonteCarloTreeSearch(
		bool(*_newStateRandFunc)(State&, State&, bool),
		char(*_judgeWin)		(State&),
		int _maxSearchTimes = 1E5
	) :
		newStateRandFunc(_newStateRandFunc),
		judgeWin		(_judgeWin),
		maxSearchTimes	(_maxSearchTimes)
	{ ; }

	/*--------------------------------------------------------------------------------
				Montecarlo Search Tree
	*[�㷨]:
		[1] ѡ��
		[2] ��չ
		[3] ģ��
		[4] ����
	--------------------------------------------------------------------------------*/
	State* run(State* state) {
		root.state = state;
		for (int i = 0; i < maxSearchTimes; i++) {
			TreeNode* expandNode = TreePolicy(&root);		//[1][2]
			if (expandNode == NULL) 
				break;

			Backpropagation(								//[4]
				expandNode, 
				Simulation(expandNode->state)				//[3]
			);
		}
		root.state = NULL;
		return Select(&root, false)->state;					//Ans
	}

	/*--------------------------------------------------------------------------------
						TreePolicy
	*	[1.ѡ��],[2.��չ]
	*	[����]: ���ڵ�
		[���]: ��չ�����ӽڵ�
	*	[����]:
			[1] ����[��չ]�ýڵ���ӽڵ�, �������ӽڵ�
			[2] ��ʧ��, ���Ǹýڵ�����,[ѡ��]�ýڵ��һ���ӽڵ���Ϊ�������, �ص�[1]
	--------------------------------------------------------------------------------*/
	TreeNode* TreePolicy(TreeNode* node) {
		TreeNode* newNode = NULL;
		while ( node != NULL && !judgeWin(*node->state)) {
			if (node->isChildFull) {
				node = Select(node, true); 
				continue;
			}
			if (Expand(node, newNode))
				return newNode;
			else {
				node->isChildFull = true;
				node = Select(node, true);
			}
		}
		return node;
	}

	/*--------------------------------[ [1]Select ѡ�� ]--------------------------------
	*	[����]: [1] �ڵ�	[2] �Ƿ�̽��
		[���]: [1] �����ӽڵ�
	*	[�㷨]: UCB��ʽ
			��Ϊ[̽��]��[��̽��]ģʽ.
	**----------------------------------------------------------------------------*/
	TreeNode* Select(TreeNode* node, bool isExplore) {
		double UcbConst = isExplore == true ? sqrt(2) : 0,
			   maxScore = -DBL_MAX;
		TreeNode* bestNode = NULL;
		for (int i = 0; i < node->child.size(); i++) {
			double t = UpperConfidenceBound(node->child[i], UcbConst);
			if (maxScore < t) {
				maxScore = t;
				bestNode = node->child[i];
			}
		}
		return bestNode;
	}

	/*-------------------------[ Upper Confidence Bound ]-----------------------------
	*Upper Confidence Bound �����Ž��㷨:
	*                              ---------------------
	*             W(node)         / In( N(parentNode) )
	*UCB(node) = --------- + C * / --------------------
	*             N(node)      ��         N(node)
	**-----------------------------------------------------------------------*/
	double UpperConfidenceBound(TreeNode* node, double C) {
		double a = (double)	   node->rewardSum			/ node->visitTime,
			   b = (double)log(node->parent->visitTime) / node->visitTime;
		return a + C * sqrt(b);
	}

	/*--------------------------------[ [2]Expand ��չ ]--------------------------------
	*	[�㷨]: 
			��������ڵ�, ���ѡ����һ��[����], ��Ϊһ�����ӽڵ㲢����.
	*	[ע]: �豣֤�����ڵ��������ڵ�[����]��ͬ.
	**----------------------------------------------------------------------------*/
	bool Expand(TreeNode* node, TreeNode*& newNode) {
		//New State
		State* newState = new State;
		if (!newStateRandFunc(*(node->state), *newState, false)) {
			delete newState; 
			return false;
		}
		//New Node
		newNode = new TreeNode;
		newNode->state  = newState;
		newNode->parent = node;
		node   ->child.push_back(newNode);
		return true;
	}

	/*--------------------------------[ [3]Simulation ģ�� ]--------------------------------
	*	[�㷨]: ������ڵ��[״̬], ����[ģ��]��ս, ֱ��ʤ��Ϊֹ.
	*	[���]: ��״̬ģ���[����]ֵ.
	**----------------------------------------------------------------------------*/
	int Simulation(State* state) {
		static State* newState = new State;
		*newState = *state;
		int reward = 0;
		while ((reward = judgeWin(*newState)) == 0)
			newStateRandFunc(*newState, *newState, true);
		return reward;
	}

	/*--------------------------------[ [4]Backpropagation ���� ]--------------------------------
	*	[�㷨]: ��[3]ģ���[����]ֵ, ��Ҷ�ڵ���������, ����ÿ����ؽڵ�.
	**----------------------------------------------------------------------------*/
	void Backpropagation(TreeNode* node, int reward) {
		while (node != NULL) {
			node->visitTime++;
			node->rewardSum += node->state->player == reward ? 1 : -1;
			node = node->parent;
		}
	}

};
#endif