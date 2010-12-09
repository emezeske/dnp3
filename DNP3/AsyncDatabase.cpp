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
#include "AsyncDatabase.h"

#include <assert.h>
#include <iostream>

#include <APL/Logger.h>

#include "DNPConstants.h"
#include "DeviceTemplate.h"


namespace apl { namespace dnp {

	AsyncDatabase::AsyncDatabase(Logger* apLogger) :
	Loggable(apLogger),
	mpEventBuffer(NULL)
	{
	
	}

	AsyncDatabase::~AsyncDatabase(){}

	//////////////////////////////////////////////////////////////////////////////
	// Public functions
	//////////////////////////////////////////////////////////////////////////////

	void AsyncDatabase::Configure(DataTypes aType, size_t aNumPoints, bool aStartOnline)
	{
		switch(aType)
		{
			case(DT_BINARY):
				this->mBinaryVec.resize(aNumPoints);
				this->AssignIndices(mBinaryVec);
				if ( aStartOnline )
					this->SetAllOnline(mBinaryVec);
				break;
			case(DT_ANALOG):
				this->mAnalogVec.resize(aNumPoints);
				this->AssignIndices(mAnalogVec);
				if ( aStartOnline )
					this->SetAllOnline(mAnalogVec);
				break;
			case(DT_COUNTER):
				this->mCounterVec.resize(aNumPoints);
				this->AssignIndices(mCounterVec);
				if ( aStartOnline )
					this->SetAllOnline(mCounterVec);
				break;
			case(DT_CONTROL_STATUS):
				this->mControlStatusVec.resize(aNumPoints);
				this->AssignIndices(mControlStatusVec);
				if ( aStartOnline )
					this->SetAllOnline(mControlStatusVec);
				break;
			case(DT_SETPOINT_STATUS):
				this->mSetpointStatusVec.resize(aNumPoints);
				this->AssignIndices(mSetpointStatusVec);
				if ( aStartOnline )
					this->SetAllOnline(mSetpointStatusVec);
				break;			
		}
	}

	void AsyncDatabase::Configure(const DeviceTemplate& arTmp)
	{
		size_t numBinary = arTmp.mBinary.size();
		size_t numAnalog = arTmp.mAnalog.size();
		size_t numCounter = arTmp.mCounter.size();
		size_t numControlStatus = arTmp.mControlStatus.size();
		size_t numSetpointStatus = arTmp.mSetpointStatus.size();

		//configure the database for these objects
		this->Configure(DT_BINARY, numBinary, arTmp.mStartOnline);
		this->Configure(DT_ANALOG, numAnalog, arTmp.mStartOnline);
		this->Configure(DT_COUNTER, numCounter, arTmp.mStartOnline);
		this->Configure(DT_CONTROL_STATUS, numControlStatus, arTmp.mStartOnline);
		this->Configure(DT_SETPOINT_STATUS, numSetpointStatus, arTmp.mStartOnline);
		
		for(size_t i=0; i<arTmp.mBinary.size(); ++i)
		{ this->SetClass(DT_BINARY, i, arTmp.mBinary[i].EventClass); }

		for(size_t i=0; i<arTmp.mCounter.size(); ++i)
		{ this->SetClass(DT_COUNTER, i, arTmp.mCounter[i].EventClass); }

		for(size_t i=0; i<arTmp.mAnalog.size(); ++i)
		{ 
			this->SetClass(DT_ANALOG, i, arTmp.mAnalog[i].EventClass); 
			this->SetDeadband(DT_ANALOG, i, arTmp.mAnalog[i].Deadband);
		}
		
		/*for(size_t i=0; i<arTmp.mControlStatus.size(); ++i)
		{ this->SetClass(DT_CONTROL_STATUS, i, arTmp.mControlStatus[i].EventClass); }
		
		for(size_t i=0; i<arTmp.mSetpointStatus.size(); ++i)
		{ this->SetClass(DT_SETPOINT_STATUS, i, arTmp.mSetpointStatus[i].EventClass); }*/
	}

	void AsyncDatabase::SetClass(DataTypes aType, PointClass aClass)
	{
		switch(aType)
		{
			case(DT_BINARY):
				for(size_t i=0; i<mBinaryVec.size(); ++i) mBinaryVec[i].mClass = aClass;
				break;
			case(DT_ANALOG):
				for(size_t i=0; i<mAnalogVec.size(); ++i) mAnalogVec[i].mClass = aClass;
				break;
			case(DT_COUNTER):
				for(size_t i=0; i<mCounterVec.size(); ++i) mCounterVec[i].mClass = aClass;
				break;
			case(DT_CONTROL_STATUS):
				for(size_t i=0; i<mControlStatusVec.size(); ++i) mControlStatusVec[i].mClass = aClass;
				break;
			case(DT_SETPOINT_STATUS):
				for(size_t i=0; i<mSetpointStatusVec.size(); ++i) mSetpointStatusVec[i].mClass = aClass;
				break;
			default:
				throw ArgumentException(LOCATION, "Class cannot be assigned for this type");
				break;
		}	
	}

	void AsyncDatabase::SetClass(apl::DataTypes aType, size_t aIndex, PointClass aClass)
	{
		switch(aType)
		{
			case(DT_BINARY):
				if(aIndex >= mBinaryVec.size()) throw Exception(LOCATION, "", ERR_INDEX_OUT_OF_BOUNDS);
				mBinaryVec[aIndex].mClass = aClass;
				break;
			case(DT_ANALOG):
				if(aIndex >= mAnalogVec.size()) throw Exception(LOCATION, "", ERR_INDEX_OUT_OF_BOUNDS);
				mAnalogVec[aIndex].mClass = aClass;
				break;
			case(DT_COUNTER):
				if(aIndex >= mCounterVec.size()) throw Exception(LOCATION, "", ERR_INDEX_OUT_OF_BOUNDS);
				mCounterVec[aIndex].mClass = aClass;
				break;
			case(DT_CONTROL_STATUS):
				if(aIndex >= mControlStatusVec.size()) throw Exception(LOCATION, "", ERR_INDEX_OUT_OF_BOUNDS);
				mControlStatusVec[aIndex].mClass = aClass;
				break;
			case(DT_SETPOINT_STATUS):
				if(aIndex >= mSetpointStatusVec.size()) throw Exception(LOCATION, "", ERR_INDEX_OUT_OF_BOUNDS);
				mSetpointStatusVec[aIndex].mClass = aClass;
				break;
			default:
				throw ArgumentException(LOCATION, "Class cannot be assigned for this type");
		}
	}

	void AsyncDatabase::SetDeadband(apl::DataTypes aType, size_t aIndex, double aDeadband)
	{
		switch(aType)
		{
			case(DT_ANALOG):
				if(aIndex >= mAnalogVec.size()) throw Exception(LOCATION, "", ERR_INDEX_OUT_OF_BOUNDS);
				mAnalogVec[aIndex].mDeadband = aDeadband;
				break;
			case(DT_COUNTER):
				if(aIndex >= mCounterVec.size()) throw Exception(LOCATION, "", ERR_INDEX_OUT_OF_BOUNDS);
				mCounterVec[aIndex].mDeadband = aDeadband;
				break;
			default:
				throw ArgumentException(LOCATION, "Deadband cannot be assigned for this type");
		}
	}

	void AsyncDatabase::SetEventBuffer(IAsyncEventBuffer* apEventBuffer)
	{
		assert(apEventBuffer != NULL);
		assert(mpEventBuffer == NULL);
		mpEventBuffer = apEventBuffer;
	}
	
	//////////////////////////////////////////////////////////////////////////////
	// IDataObserver interface - Private NVII functions - 
	//////////////////////////////////////////////////////////////////////////////

	void AsyncDatabase::_Update(const apl::Binary& arPoint, size_t aIndex)
	{
		if(UpdateValue<apl::Binary>(mBinaryVec, arPoint, aIndex))
		{
			LOG_BLOCK(LEV_DEBUG, "Binary Change: " << arPoint.ToString() << " Index: " << aIndex);
			BinaryInfo& v = mBinaryVec[aIndex];
			if(mpEventBuffer) mpEventBuffer->Update(v.mValue, v.mClass, aIndex);
		}
	}

	void AsyncDatabase::_Update(const apl::Analog& arPoint, size_t aIndex)
	{
		if(UpdateValue<apl::Analog>(mAnalogVec, arPoint, aIndex))
		{
			LOG_BLOCK(LEV_DEBUG, "Analog Change: " << arPoint.ToString() << " Index: " << aIndex);
			mAnalogVec[aIndex].mLastEventValue = mAnalogVec[aIndex].mValue.GetValue();
			AnalogInfo& v = mAnalogVec[aIndex];
			if(mpEventBuffer) mpEventBuffer->Update(v.mValue, v.mClass, aIndex);
		}
	}
	
	void AsyncDatabase::_Update(const apl::Counter& arPoint, size_t aIndex)
	{
		if(UpdateValue<apl::Counter>(mCounterVec, arPoint, aIndex))
		{
			LOG_BLOCK(LEV_DEBUG, "Counter Change: " << arPoint.ToString() << " Index: " << aIndex);
			mCounterVec[aIndex].mLastEventValue = mCounterVec[aIndex].mValue.GetValue();
			CounterInfo& v = mCounterVec[aIndex];
			if(mpEventBuffer) mpEventBuffer->Update(v.mValue, v.mClass, aIndex);
		}
	}

	void AsyncDatabase::_Update(const apl::ControlStatus& arPoint, size_t aIndex)
	{
		UpdateValue<apl::ControlStatus>(mControlStatusVec, arPoint, aIndex); 
	}

	void AsyncDatabase::_Update(const apl::SetpointStatus& arPoint, size_t aIndex)
	{
		UpdateValue<apl::SetpointStatus>(mSetpointStatusVec, arPoint, aIndex); 
	}
	
	//////////////////////////////////////////////////////////////////////////////
	// misc public functions
	//////////////////////////////////////////////////////////////////////////////

	size_t AsyncDatabase::MaxIndex(DataTypes aType)
	{
		size_t num = NumType(aType);
		if(num == 0) throw ArgumentException(LOCATION, "No points for datatype");
		else return (num-1);
	}

	size_t AsyncDatabase::NumType(DataTypes aType)
	{
		switch(aType)
		{
			case(DT_BINARY):
				return mBinaryVec.size();
			case(DT_ANALOG):
				return mAnalogVec.size();
			case(DT_COUNTER):
				return mCounterVec.size();
			case(DT_CONTROL_STATUS):
				return mControlStatusVec.size();
			case(DT_SETPOINT_STATUS):
				return mSetpointStatusVec.size();
		}

		return 0;
	}

}}

