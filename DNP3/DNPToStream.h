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
#ifndef __DNP_TO_STREAM_H_
#define __DNP_TO_STREAM_H_

#include <APL/Configure.h>
#include <APL/DataTypes.h>
#include <APL/CommandTypes.h>
//#include "ObjectInterfaces.h"
//#include "Objects.h"

#ifdef APL_PLATFORM_WIN
//disable the type conversion warnings
#pragma warning ( push )
#pragma warning ( disable : 4244 )
#endif

namespace apl { namespace dnp {

	class DNPToStream
	{
		public:

			// Templates for writing to stream
			template <typename T, typename U>
			static void WriteQ(apl::byte_t* apPos, const T* apObj, const U& arObj);

			template <typename T, typename U>
			static void WriteQV(apl::byte_t* apPos, const T* apObj, const U& arObj);

			template <typename T, typename U>
			static void WriteQT(apl::byte_t* apPos, const T* apObj, const U& arObj);

			template <typename T, typename U>
			static void WriteCheckRangeQV(apl::byte_t* apPos, const T* apObj, const U&  arObj);

			template <typename T, typename U>
			static void WriteV(apl::byte_t* apPos, const T* apObj, const U&  arObj);

			template<typename T, typename U>
			static void WriteQVT(apl::byte_t* apPos, const T* apObj, const U&  arObj);

			template<typename T, typename U>
			static void WriteCheckRangeQVT(apl::byte_t* apPos, const T* apObj, const U&  arObj);
	};

	template <class T, class U>
	class Conversion
	{
		public:
		static U Convert(T aVal) { return aVal; } //try implicit casting
	};

	//this partial specialization allows us to change how doubles are converted
	template <class U>
	class Conversion<double, U>
	{
		public:
		static U Convert(double aVal) {
			return static_cast<U>(aVal);
		}
	};

	template <typename T, typename U>
	inline void DNPToStream::WriteQ(apl::byte_t* apPos, const T* apObj, const U& arObj)
	{
		apObj->mFlag.Set(apPos, arObj.GetQuality());
	}

	template <typename T, typename U>
	inline void DNPToStream::WriteQT(apl::byte_t* apPos, const T* apObj, const U& arObj)
	{
		apObj->mFlag.Set(apPos, arObj.GetQuality());
		apObj->mTime.Set(apPos, arObj.GetTime());
	}

	// Templates for writing to stream
	template <typename T, typename U>
	void DNPToStream::WriteCheckRangeQV(apl::byte_t* apPos, const T* apObj, const U& arObj)
	{
		apl::byte_t qual = arObj.GetQuality();

		typename U::Type val = arObj.GetValue();
		if(val > apObj->mValue.Max())
		{ val = apObj->mValue.Max(); qual |= apObj->mValue.OverRangeMask(); }
		if(val < apObj->mValue.Min())
		{ val = apObj->mValue.Min(); qual |= apObj->mValue.OverRangeMask(); }

		apObj->mFlag.Set(apPos, qual);
		apObj->mValue.Set(apPos, Conversion<typename U::Type, typename T::Type>::Convert(val));
	}

	// Templates for writing to stream
	template <typename T, typename U>
	void DNPToStream::WriteV(apl::byte_t* apPos, const T* apObj, const U& arObj)
	{
		typename U::Type val = arObj.GetValue();
		if(val > apObj->mValue.Max())
		{ val = apObj->mValue.Max(); }
		if(val < apObj->mValue.Min())
		{ val = apObj->mValue.Min(); }

		apObj->mValue.Set(apPos, Conversion<typename U::Type, typename T::Type>::Convert(val));
	}

	// Templates for writing to stream
	template <typename T, typename U>
	inline void DNPToStream::WriteQV(apl::byte_t* apPos, const T* apObj, const U& arObj)
	{
		apObj->mFlag.Set(apPos, arObj.GetQuality());
		WriteV<T,U>(apPos, apObj, arObj);
	}

	template<typename T, typename U>
	void DNPToStream::WriteQVT(apl::byte_t* apPos, const T* apObj, const U&  arObj)
	{
		WriteQV<T,U>(apPos, apObj, arObj);
		apObj->mTime.Set(apPos, arObj.GetTime());
	}

	template<typename T, typename U>
	inline void DNPToStream::WriteCheckRangeQVT(apl::byte_t* apPos, const T* apObj, const U& arObj)
	{
		WriteCheckRangeQV<T,U>(apPos, apObj, arObj);
		apObj->mTime.Set(apPos, arObj.GetTime());
	}

}}

#ifdef APL_PLATFORM_WIN
//disable the type conversion warnings
#pragma warning ( pop )
#endif

#endif

