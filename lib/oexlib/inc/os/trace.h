/*------------------------------------------------------------------
// trace.h
//
// Copyright (c) 1997
// Robert Umbehant
// winglib@wheresjames.com
// http://www.wheresjames.com
//
// Redistribution and use in source and binary forms, with or
// without modification, are permitted for commercial and
// non-commercial purposes, provided that the following
// conditions are met:
//
// * Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// * The names of the developers or contributors may not be used to
//   endorse or promote products derived from this software without
//   specific prior written permission.
//
//   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
//   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
//   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
//   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
//   OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//   EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//----------------------------------------------------------------*/
#pragma once

//==================================================================
// CTrace
//
/// Os independent stack tracing functions
/**

*/
//==================================================================
class CTrace
{
private:
	CTrace() {}
	virtual ~CTrace() {}

public:

	//==============================================================
	// GetBacktrace()
	//==============================================================
	/// Returns a human readable stacktrace
	/**
		\param [in] x_uSkip - Number of functions to skip from the
							  top of the stack.
		\param [in] x_uMax	- Maximum number of functions to return

		\return Module instance handle

		\see
	*/
	static CStr GetBacktrace( oexUINT x_uSkip = 0, oexUINT x_uMax = 100 );


	//==============================================================
	// GetErrorMsg()
	//==============================================================
	/// Returns a human readable description of the error code
	/**
		\param [in] x_nErr		-	Error code to look up.

		\return Returns the error code

		\see
	*/
	static CStr GetErrorMsg( oexINT x_nErr );

	//==============================================================
	// GetLastError()
	//==============================================================
	/// Returns a value signifying the last error that occured
	/**
		\return Returns the error code

		\see
	*/
	static oexINT GetLastError();

};
