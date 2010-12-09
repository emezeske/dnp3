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
#ifndef __TLS_BASE_H_
#define __TLS_BASE_H_


#include <APL/Types.h>
#include <APL/Uncopyable.h>

#include <string>

namespace apl { namespace dnp {

	class AsyncTransportLayer;


	/**
	Base class for all TransportLayerStates (TLS)
	*/
	class TLS_Base
	{
		public:
			virtual void Send(const apl::byte_t*, size_t, AsyncTransportLayer*);
			virtual void HandleReceive(const apl::byte_t*, size_t, AsyncTransportLayer*);

			// TPDU failure/success handlers
			virtual void HandleSendSuccess(AsyncTransportLayer*);
			virtual void HandleSendFailure(AsyncTransportLayer*);

			virtual void LowerLayerUp(AsyncTransportLayer*);
			virtual void LowerLayerDown(AsyncTransportLayer*);

			virtual std::string Name() const = 0;
	};



}}

#endif
