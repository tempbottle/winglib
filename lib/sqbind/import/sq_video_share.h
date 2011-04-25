/*------------------------------------------------------------------
// sq_video_share.h
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

namespace sqbind
{
    class CSqVideoShare
    {
	public:
	
		// Key values
#		define SQSVS_PREFIX		oexT( "oex_video_share_" )
#		define SQSVS_CBID		0xBEBADDBA
	
	public:

		/// Export constructors
		SQBIND_CLASS_CTOR_BEGIN( CSqVideoShare )
			_SQBIND_CLASS_CTOR2( CSqVideoShare, OT_STRING, OT_INTEGER ) 
				( stdString( sa.GetString( 2 ), sq_getsize( x_v, 2 ) ), sa.GetInt( 3 ), 1 )
			_SQBIND_CLASS_CTOR3( CSqVideoShare, OT_STRING, OT_INTEGER, OT_INTEGER ) 
				( stdString( sa.GetString( 2 ), sq_getsize( x_v, 2 ) ), sa.GetInt( 3 ), sa.GetInt( 4 ) )
		SQBIND_CLASS_CTOR_END( CSqVideoShare )

		/// Default constructor
		CSqVideoShare();

		/// Init constructor
		CSqVideoShare( const sqbind::stdString &sPrefix, SQInteger nId, SQInteger nGlobal );

		/// Copy constructor
		CSqVideoShare( const CSqVideoShare &r );

		/// Assignment operator
		CSqVideoShare& operator = ( const CSqVideoShare &r ) { return *this; }

		/// Registers the class
		static void Register( sqbind::VM vm );

		/** \addtogroup CSqVideoShare
			@{
		*/
		
		/// Releases the share and all associated resources
		void Destroy();
		
		/// Creates a writable share
		/**
			@param [in] sName		-	Share name
			@param [in] nBuffers	-	Number of video buffers to allocate
			@param [in] nImgSize	-	Size of a single image frame
			@param [in] nWidth		-	Width of a video frame
			@param [in] nHeight		-	Height of a video frame
			@param [in] nFps		-	Frames per second
			@param [in] nFmt		-	User defined video format id
			
			Opens a new writable share.  This function fails if the share already exists.
			
			@return Non-zero if success
		
		*/
		int Create( const sqbind::stdString &sName, int nBuffers, int nImgSize, int nWidth, int nHeight, int nFps, int nFmt );

		/// Opens an existing share
		/**
			@param [in] sName					-	Share name
			@param [in] bAllowFrameSkipping		-	Non-zero to allow frame skipping
			
			Opens an existing video share.  The share must exist.
			
			If you want to process each frame, such as if you are saving to an avi,
			then set bAllowFrameSkipping to zero.
			
			If you just want to receive the latest frame, such as in a preview window,
			set bAllowFrameSkipping to a non-zero value.
			
			@return Non-zero if success
		*/
		int Open( const sqbind::stdString &sName, int bAllowFrameSkipping );

		/// Return the share name
		sqbind::stdString getName() { return m_sName; }
		
		/// Sets the prefix string
		void setPrefix( const sqbind::stdString &s ) { m_sPrefix = s; }
		
		/// Returns the current prefix string
		sqbind::stdString getPrefix() { return m_sPrefix; }
		
		/// Sets the control block id
		void setCbId( oex::oexUINT id ) { m_uCbId = id; }
		
		/// Gets the control block id
		oex::oexUINT getCbId() { return m_uCbId; }
				
		/// Set to non-zero to enable global access to share
		void setGlobal( int b ) { m_bGlobal = b; }
		
		/// Returns non-zero if global access to share is enabled
		int getGlobal() { return m_bGlobal; }

		/// Returns the number of image buffers from the control block
		int getBuffers()
		{	if ( !m_cb.getUsed() ) 
				return 0;
			return m_cb.getINT( 2 );
		}

		/// Returns the image width from the control block
		int getWidth()
		{	if ( !m_cb.getUsed() ) 
				return 0;
			return m_cb.getINT( 3 );
		}
		
		/// Returns the image height from the control block
		int getHeight()
		{	if ( !m_cb.getUsed() ) 
				return 0;
			return m_cb.getINT( 4 );
		}
		
		/// Returns the frames per second value from the control block
		int getFps()
		{	if ( !m_cb.getUsed() ) 
				return 0;
			return m_cb.getINT( 5 );
		}
		
		/// Returns the image size from the control block
		int getImageSize()
		{	if ( !m_cb.getUsed() ) 
				return 0;
			return m_cb.getINT( 7 );
		}
		
		/// Set to non-zero to allow frame skipping
		void setAllowFrameSkipping( int b ) { m_bAllowFrameSkipping = b; }
		
		/// Returns non-zero if frame skipping is enabled
		int getAllowFrameSkipping() { return m_bAllowFrameSkipping; }
		
		/// Returns a string describing the last error
		sqbind::stdString getLastErrorStr() { return m_sLastErr; }
		
		/// Sets the last error string
		void setLastErrorStr( const sqbind::stdString &sErr ) { m_sLastErr = sErr; }

		/// Reads the next available image from the video share
		/**
			A shared buffer must be open.  Returns an empty CSqBinary
			object if no new frame is available.
			
			There can be multiple readers on a single shared buffer, 
			but only one per CSqVideoShare class instance.
		*/
		sqbind::CSqBinary getNextImg();
		
		/// Reads the last available image from the video share
		sqbind::CSqBinary getLastImg();

		/// Returns the buffer for the next write
		sqbind::CSqBinary getWriteImg();
		
		/// Increments the write pointer
		int incWritePtr();
		
		/// Writes a frame to the shared buffer
		/**
			@param [in] frame	-	Frame of video data to write
			
			Writes the frame and increments the index pointer to alert the reader(s)
			
			@return Non zero if success
		
		*/
		int WriteFrame( sqbind::CSqBinary *frame );
		
		
		/** @} */
	
	private:
	
		/// Non-zero for global share
		int						m_bGlobal;

		/// Non-zero if the share is open for writing
		int						m_bWrite;
		
		/// Non-zero to allow frame skipping
		int						m_bAllowFrameSkipping;
		
		/// Control block id
		oex::oexUINT			m_uCbId;
	
		/// The share name
		sqbind::stdString		m_sName;
	
		/// Share prefix
		sqbind::stdString		m_sPrefix;

		/// The shared control block
		CSqBinary				m_cb;

		/// The shared buffer
		CSqBinary				m_buf;
		
		/// String describing the last error
		sqbind::stdString		m_sLastErr;
		
		/// Current read index
		int						m_iRead;

	};

}; // end namespace

// Declare type for use as squirrel parameters
SQBIND_DECLARE_INSTANCE( sqbind::CSqVideoShare, CSqVideoShare )
