// 
// Licensed to Green Energy Corp (www.greenenergycorp.com) under one
// or more contributor license agreements. See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  Green Energy Corp licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
//  
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
// 
#include "EventLock.h"



namespace apl
{

//////////////////////////////////////////////////////////
// EventLock
//////////////////////////////////////////////////////////

EventLock::EventLock() : 
EventLockBase<int_64_t>(), 
mEvents(~static_cast<int_64_t>(0))
{} //set all events by default so we don't miss anything


void EventLock::RecordEventCode(const apl::int_64_t& arEvent) 
{ this->mEvents |= arEvent; }


//needs to be used only when we are already locked on the object
int_64_t EventLock::GetEvents(bool aClearSentEvents){
	int_64_t temp = mEvents;
	if(aClearSentEvents) mEvents = 0;
	return temp;
}

int_64_t EventLock::Get64BitMask(size_t aShift)
{
	int_64_t m = 1;
	m = m << aShift;
	return m;
}


}

