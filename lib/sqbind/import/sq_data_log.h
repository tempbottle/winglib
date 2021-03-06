/*------------------------------------------------------------------
// sq_data_log.h
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

// namespace
namespace sqbind
{
	class CSqDataLog
	{
	public:

		SQBIND_CLASS_CTOR_BEGIN( CSqDataLog )
//			_SQBIND_CLASS_CTOR( CSqDataLog, 1 ) ( sa.GetInt( 2 ) )
		SQBIND_CLASS_CTOR_END( CSqDataLog )

		/// Default constructor
		CSqDataLog() {}

		/// Copy constructor
		CSqDataLog( const CSqDataLog &r ) { }

		/// Assignment operator
		CSqDataLog& operator = ( const CSqDataLog &r ) { return *this; }

		/// Registers the class
		static void Register( sqbind::VM vm );

		/// Frees the resources
		void Destroy() { m_it.Destroy(); m_dl.Destroy(); }

		/// Sets the root path for the data logs
		void setRoot( const stdString &sRoot ) { m_dl.SetRoot( sRoot.c_str() ); }

		/// Returns the root path of the data logs
		stdString getRoot() { return oex2std( m_dl.GetRoot() ); }

		/// Returns the log base
		SQINT getBase() { return m_dl.GetBase(); }

		/// Returns the index step size
		SQINT getStep() { return m_dl.GetStep(); }

		/// Adds a key to the data log
		/**
			\param [in] sName	-	Key name
			\param [in] nTime	-	Time first entry will be made, zero uses 
									the current time.  This allows resuming a
									previous key.

			\return Less than zero on failure, otherwise, the new key index.
		*/
		SQINT AddKey( const stdString &sName, SQINT nTime )
		{	return m_dl.AddKey( sName.c_str(), nTime ); }

		/// Removes the specified key by index
		SQINT RemoveKey( SQINT nKey )
		{	return m_dl.RemoveKey( nKey ); }

		/// Finds index of the named key
		SQINT FindKey( const stdString &sName )
		{	return m_dl.FindKey( sName.c_str() ); }

		/// Logs the specified data
		SQINT Log( SQINT nKey, CSqBinary *pBin, SQINT nTime, SQINT nTimeMs, SQINT nBuffering )
		{	if ( !pBin ) return 0; return m_dl.Log( nKey, pBin->Ptr(), pBin->getUsed(), nTime, nTimeMs, nBuffering ); }

		/// Flushes the specified data to disk
		SQINT Flush( SQINT nTime )
		{	return m_dl.Flush( nTime ); }

		/// Returns the amount of data buffered on the specified logging key
		SQINT getBufferSize( SQINT nKey )
		{	return m_dl.GetBufferSize( nKey ); }

		/// Set up log params
		void setLogParams( SQINT nBase, SQINT nStep )
		{	m_dl.SetLogParams( nBase, nStep ); }

		/// Returns a list of keys using the index for the specified time
		CSqMulti getKeyList( SQINT nTime );

		/// Returns the log data for the specified time range
		CSqMulti getLog( const stdString &sKey, SQINT nStart, SQINT nEnd, SQINT nInterval, SQINT nType, SQINT nMethod );

		/// Returns the log for the specified key and time range in a shared binary buffer
		stdString getLogBin( const stdString &sKey, SQINT nStart, SQINT nEnd, SQINT nInterval, SQINT nType, SQINT nMethod, SQFLOAT fScale )
		{	return oex2std( m_dl.GetLogBin( sKey.c_str(), nStart, nEnd, nInterval, nType, nMethod, fScale ) ); }
		
		/// Sets the fetch limit
		void setLimit( int nLimit ) { m_dl.SetLimit( (oex::oexUINT)nLimit ); }

		/// Returns the fetch limit
		int getLimit() { return (int)m_dl.GetLimit(); }

		/// Starts iteration
		SQINT itStart( const stdString &sKey, SQINT nTime, SQINT nTimeMs )
		{
			// Cancel any previous iteration
			m_it.Destroy();

			// Start iterator
			if ( !m_it.Init( m_dl.GetRoot(), sKey.c_str() ) || !m_it.IsData( m_dl.GetBase(), nTime ) )
				return 0;

			// Find the first matching value
			if ( !m_dl.FindValue( m_it, nTime, nTimeMs, 1, 
								  oex::obj::tInvalid, oex::CDataLog::eMethodDiscrete | oex::CDataLog::eMethodNoRead,
								  m_dl.GetBase(), m_dl.GetStep() ) )
				return 0;

			// Backup one if there's no object here
			if ( !m_it.getValueSize() )
				itPrev();

			return m_it.getValueSize();
		}

		/// Next item
		SQINT itNext()
		{	return m_dl.FindValue( m_it, m_it.viNext.uTime, m_it.viNext.uTimeMs, 0, 
									oex::obj::tInvalid, oex::CDataLog::eMethodDiscrete | oex::CDataLog::eMethodNoRead,
									m_dl.GetBase(), m_dl.GetStep() );
		}

		/// Previous item
		SQINT itPrev()
		{	return m_dl.FindValue( m_it, m_it.viNext.uTime, m_it.viNext.uTimeMs, 0, 
									oex::obj::tInvalid, 
									oex::CDataLog::eMethodDiscrete | oex::CDataLog::eMethodReverse | oex::CDataLog::eMethodNoRead,
									m_dl.GetBase(), m_dl.GetStep() );
		}

		/// Read item data
		CSqBinary itRead()
		{	return m_it.getValueBin(); }

		/// Close iterator
		void itClose() { m_it.Destroy(); }

		/// Time
		SQINT itTime() { return m_it.vi.uTime; }

		/// Time Milliseconds
		SQINT itTimeMs() { return m_it.vi.uTimeMs; }

		/// Data size
		SQINT itSize() { return m_it.vi.uSize; }

		/// Access to wrapped object
		oex::CDataLog& Obj() { return m_dl; }

	private:

		/// Iterator
		oex::CDataLog::SIterator		m_it;

		/// Data log object
		oex::CDataLog					m_dl;

	};

}; // end namespace

// Declare type for use as squirrel parameters
SQBIND_DECLARE_INSTANCE( sqbind::CSqDataLog, CSqDataLog )
