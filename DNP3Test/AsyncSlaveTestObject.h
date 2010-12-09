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
#ifndef __ASYNC_SLAVE_TEST_OBJECT_H_
#define __ASYNC_SLAVE_TEST_OBJECT_H_

#include <APLTestTools/MockTimerSource.h>
#include <APL/AsyncTaskScheduler.h>
#include <APLTestTools/LogTester.h>
#include <APLTestTools/MockCommandAcceptor.h>
#include <DNP3/AsyncSlave.h>
#include <DNP3/AsyncDatabase.h>
#include <DNP3/DNPCommandMaster.h>
#include <DNP3/SlaveConfig.h>

#include "MockAsyncAppLayer.h"

namespace apl { namespace dnp {

class AsyncSlaveTestObject : public LogTester
{
	public:
	AsyncSlaveTestObject(const SlaveConfig& arCfg, FilterLevel aLevel = LEV_INFO, bool aImmediate = false);

	void SendToSlave(const std::string& arData, SequenceInfo aSeq = SI_OTHER);
	std::string Read();
	size_t Count() { return app.Count(); }


	//MockTimeSource fake_time;
	MockTimeManager fakeTime;
	MockTimerSource mts;
	MockAsyncAppLayer app;
	AsyncDatabase db;
	DNPCommandMaster cmd_master;
	MockCommandAcceptor cmd_acceptor;
	AsyncSlave slave;
	APDU mAPDU;
	Logger* mpLogger;

};

}}

#endif
