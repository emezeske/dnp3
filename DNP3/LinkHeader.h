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
#ifndef __LINK_HEADER_H_
#define __LINK_HEADER_H_


#include "LinkLayerConstants.h"

namespace apl { namespace dnp {

/// Class for dealing with all aspects of FT3 Frame headers
struct LinkHeader
{
	LinkHeader();

	LinkHeader(byte_t aLen, uint_16_t aSrc, uint_16_t aDest, bool aFromMaster, bool aFcvDfc, bool aFcb, FuncCodes aCode);

	/** @param apBuff Buffer of at least 10 bytes*/
	LinkHeader(const byte_t* apBuff);

	/// Setter

	void Set(byte_t aLen, uint_16_t aSrc, uint_16_t aDest, bool aFromMaster, bool aFcvDfc, bool aFcb, FuncCodes aCode);

	void ChangeFCB(bool aFCB);

	// Getters
	byte_t GetLength() const { return length; }
	uint_16_t GetDest() const { return dest; }
	uint_16_t GetSrc() const { return src; }
	bool IsFromMaster() const { return (ctrl & MASK_DIR) != 0; }
	bool IsPriToSec() const { return (ctrl & MASK_PRM) != 0; }
	bool IsFcbSet() const { return (ctrl & MASK_FCB) != 0; }
	bool IsFcvDfcSet() const { return (ctrl & MASK_FCV) != 0; }
	byte_t GetFuncByte() const { return ctrl & MASK_FUNC; }
	FuncCodes GetFuncEnum() const { return ByteToFuncCode(ctrl & MASK_FUNC_OR_PRM); }

	bool ValidLength() { return length > 4; }

	/** Reads the header, setting all the fields. Does NOT validate 0x0564 or CRC
	@param apBuff Buffer of at least 10 bytes */
	void Read(const byte_t* apBuff);

	/** Writes header to buffer including, 0x0564 and CRC
	@param apBuff Buffer of at least 10 bytes */
	void Write(byte_t* apBuff) const;

	std::string ToString() const;

	static byte_t ControlByte(bool aIsMaster, bool aFcb, bool aFcvDfc, FuncCodes aFunc);

	private:

	// Fields read directly from the header
	byte_t length;	/// Length of field, range [5,255] valid
	uint_16_t src;	/// Where the frame originated
	uint_16_t dest;	/// Where the frame is going
	byte_t ctrl;	/// Control octet, individual fields accessed using accessors below
};


}}

#endif
