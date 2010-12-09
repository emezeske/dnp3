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
#ifndef __ASYNC_DATABASE_INTERFACES_H_
#define __ASYNC_DATABASE_INTERFACES_H_


#include "DNPDatabaseTypes.h"
#include <APL/DataInterfaces.h>
#include <APL/PackingUnpacking.h>

namespace apl {
class INotifier;
}

namespace apl{ namespace dnp {

/// @section desc Used by the database
class IAsyncEventBuffer
{
	public:

	virtual ~IAsyncEventBuffer() {}

	/// @return true if the event buffer accepts the event, false otherwise
	virtual void Update(const Binary& arEvent, PointClass aClass, size_t aIndex) = 0;

	/// @return true if the event buffer accepts the event, false otherwise
	virtual void Update(const Analog& arEvent, PointClass aClass, size_t aIndex) = 0;

	/// @return true if the event buffer accepts the event, false otherwise
	virtual void Update(const Counter& arEvent, PointClass aClass, size_t aIndex) = 0;

};

}}

#endif

