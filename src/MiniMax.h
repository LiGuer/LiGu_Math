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
#ifndef MINIMAX_H
#define MINIMAX_H
#include <vector>
template<class State>
class MiniMax {
public:
	int MaxLevel = 5;
	int  (*Evaluate)		(State&);					//���ۺ���
	bool (*newStateFunc)	(State&, State&);			//������״̬
	signed char
		 (*judgeTerminate)	(State&);					//�ж���Ӯ
	void (*endingState)		(State&);					//״̬��β����
	std::vector<int> ansRewardSet;
	State maxRewardState;
	/*----------------[ ����/�������� ]----------------*/
	MiniMax(
		int (*_Evaluate)		(State&), 
		bool(*_newStateFunc)	(State&, State&), 
		signed char
			(*_judgeTerminate)	(State&),
		void(*_endingState)		(State&),
		int _MaxLevel = 5
	) {
		Evaluate       = _Evaluate;
		newStateFunc   = _newStateFunc;
		judgeTerminate = _judgeTerminate;
		endingState    = _endingState;
		MaxLevel	   = _MaxLevel;
	}
	/******************************************************************************
	*                    ���ߺ���  ������
	*	[����]:
			[0] ���������ֵ, ���ص�ǰ״̬������(���ۺ���)
			[1] ���ڵ�ǰ״̬, ������״̬, ����ÿһ�����ܵ���״̬
				[2] �ݹ���ߺ���, ���������������&����������
				[3] ��β
					[3.1] �������Ĳ�(���ֲ�) ȡ��С
					[3.2] ˫�����Ĳ�(��  ��) ȡ���
					[3.3] alpha-beta��֦
	******************************************************************************/
	int Policy(State& state, int alpha = -0x7fffffff, int beta = 0x7fffffff, int level = 0) {
		//[0]
		if (level > MaxLevel || judgeTerminate(state) != 0)
			return Evaluate(state);
		int max = -0x7fffffff, 
			min =  0x7fffffff;
		//[1]
		State newState;
		while (newStateFunc(state, newState)) {
			//[2]
			int reward = Policy(newState, alpha, beta, level + 1);
			//[3]
			if (level == 0) {
				ansRewardSet.push_back(reward);
				if (reward > max) 
					maxRewardState = newState;
			}
			if (level % 2 == 0)
				max = max >= reward ? max : reward, alpha = alpha >= reward ? alpha : reward;
			else 
				min = min <= reward ? min : reward,  beta =  beta <= reward ?  beta : reward;

			if (alpha >= beta) break;
		}
		endingState(newState);
		return level % 2 == 0 ? max : min;
	}
};
#endif