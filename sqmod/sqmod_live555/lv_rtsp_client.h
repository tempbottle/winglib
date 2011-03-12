// lv_rtsp_client.h

class CLvRtspClient : oex::CThread
{
public:

	class CVideoSink : public MediaSink
	{
	public:

		enum
		{
            eDefaultBufferSize = 2000000
		};

	public:

		/// Constructor
		CVideoSink( UsageEnvironment &rEnv );
		virtual ~CVideoSink();

		/// Returns non-zero if new frame is needed
		int needFrame();

		/// Reads frame info
		int LockFrame( sqbind::CSqBinary *dat, int to );

		/// Releases the frame buffer
		int UnlockFrame();

		/// Sets the packet header
		void setHeader( sqbind::CSqBinary *header );

		/// Grabs next frame
		virtual Boolean continuePlaying();

	private:

		/// Destructor
//		virtual ~CVideoSink();

	private:

		static void _afterGettingFrame( void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
										struct timeval presentationTime, unsigned durationInMicroseconds );

		/// Processes new frames
		void afterGettingFrame( void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
								struct timeval presentationTime, unsigned durationInMicroseconds );

	private:

		/// Packet header to add
		sqbind::CSqBinary		m_header;

		/// Data buffer
		sqbind::CSqBinary		m_buf;

		/// Non-zero when a new frame is ready
		int						m_nFrameReady;

		/// Non-zero when a new frame is being captured
		int						m_nFrameGrabbing;

		/// Data lock
		oexLock					m_lock;

	};

	class CAudioSink : public MediaSink // public MPEG4LATMAudioRTPSink 
	{
	public:

		enum
		{
            eDefaultBufferSize = 2000000
		};

	public:

		/// Constructor
		CAudioSink( UsageEnvironment &rEnv );
		virtual ~CAudioSink();

        /// Reads frame infofile:///home/landshark/code/lib2/winglib/sqmod/sqmod_live555/lv_rtsp_server.cpp

		/// Returns non-zero if new frame is needed
		int needFrame();

		int LockFrame( sqbind::CSqBinary *dat, int to );

		/// Releases the frame buffer
		int UnlockFrame();

		/// Grabs next frame
		virtual Boolean continuePlaying();

	private:

		/// Destructor
//		virtual ~CAudioSink();

	private:

		static void _afterGettingFrame( void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
										struct timeval presentationTime, unsigned durationInMicroseconds );

		/// Processes new frames
		void afterGettingFrame( void* clientData, unsigned frameSize, unsigned numTruncatedBytes,
								struct timeval presentationTime, unsigned durationInMicroseconds );

	private:

		/// Data buffer
		sqbind::CSqBinary		m_buf;

		/// Non-zero when a new frame is ready
		int						m_nFrameReady;

		/// Non-zero when a new frame is being captured
		int						m_nFrameGrabbing;

	};


public:

	// Declare constructors
	_SQBIND_CLASS_CTOR_BEGIN( CLvRtspClient )
	_SQBIND_CLASS_CTOR_END( CLvRtspClient )

	/// Default constructor
	CLvRtspClient();

	/// Destructor
	virtual ~CLvRtspClient() { Destroy(); }

	/// Copy
	CLvRtspClient( const CLvRtspClient &r ) { }
	CLvRtspClient& operator = ( const CLvRtspClient &r ) { return *this; }

	/// Destroy connection
	void Destroy();

	/// Open link
	int Open( const sqbind::stdString &sUrl, int bVideo, int bAudio, sqbind::CSqMulti *m );

	/// Thread open
	int ThreadOpen( const sqbind::stdString &sUrl, int bVideo, int bAudio, sqbind::CSqMulti *m );

	/// Reads frame data, good until UnlockFrame() is called
	int LockVideo( sqbind::CSqBinary *dat, int to );

	/// Releases the frame buffer
	int UnlockVideo();

	/// Reads frame data, good until UnlockFrame() is called
	int LockAudio( sqbind::CSqBinary *dat, int to );

	/// Releases the frame buffer
	int UnlockAudio();

	/// Returns video width
	int getWidth()
	{	return m_width;
	}

	/// Returns video width
	int getHeight()
	{	return m_height;
	}

	/// Returns video width
	int getFps()
	{	return m_fps;
	}

	/// Returns the sdp object
	sqbind::CSqMulti getSDP()
	{	return m_mSdp;
	}

	/// Returns a single sdp value
	sqbind::CSqMulti getSDPValue( const sqbind::stdString &k )
	{	return m_mSdp[ k ];
	}

	/// Returns non-zero if a container is open
	int isOpen()
	{	return m_pRtspClient ? 1 : 0;
	}

	/// Return the frame count
	int getFrameCount()
	{	return m_nFrames;
	}

	/// Returns the video codec name
	sqbind::stdString getVideoCodecName()
	{	return m_sVideoCodec; }

	/// Returns the audio codec name
	sqbind::stdString getAudioCodecName()
	{	return m_sAudioCodec; }

	/// waits for the application to initialize
	int waitInit( int nMax )
	{	return !GetInitEvent().Wait( nMax ); }

	/// Returns non-zero if video was enabled and the open stream contains video
	int isVideo()
	{	return m_bVideo; }

	/// Returns non-zero if audio was enabled and the open stream contains audio
	int isAudio()
	{	return m_bAudio; }

	/// Returns a pointer to the any extra codec data
	sqbind::CSqBinary getExtraVideoData() { return m_extraVideo; }

	/// Returns a pointer to the any extra codec data
	sqbind::CSqBinary getExtraAudioData() { return m_extraAudio; }

	/// Sets the video header
	void setVideoHeader( sqbind::CSqBinary *header )
	{	if ( m_pVs ) m_pVs->setHeader( header );
	} // end

	/// Signal start
	void Play() { m_evtPlay.Signal(); }

	/// Idle processing static function
	static void _OnIdle( void *pData );

	/// Idle processing
	void OnIdle();

protected:

	/// Initializes thread
	virtual oex::oexBOOL InitThread( oex::oexPVOID x_pData );

	/// Runs the thread
	virtual oex::oexBOOL DoThread( oex::oexPVOID x_pData );

	/// Cleanup
	virtual oex::oexINT EndThread( oex::oexPVOID x_pData );

	/// Thread cleanup
	void ThreadDestroy();

	/// Initializes video stream
	int InitVideo( MediaSubsession *pss );

	/// Initializes video stream
	int InitAudio( MediaSubsession *pss );

private:

	/// Flag to end loop
	char					m_nEnd;

	/// Url to open
	sqbind::stdString		m_sUrl;

	/// Non-zero if video should be processed
	int						m_bVideo;

	/// Non-zero if audio should be processed
	int						m_bAudio;

	/// The name of the video codec
	sqbind::stdString		m_sVideoCodec;

	/// The name of the video codec
	sqbind::stdString		m_sAudioCodec;

	/// Parameters
	sqbind::CSqMulti		m_mParams;

	/// Usage environment
	UsageEnvironment		*m_pEnv;

	/// RTSP client object
	RTSPClient				*m_pRtspClient;

	/// Session object
	MediaSession			*m_pSession;

	/// Video sink
	CVideoSink				*m_pVs;

	/// Video sub session
	MediaSubsession			*m_pVsPss;

	/// Audio sink
	CAudioSink				*m_pAs;

	/// Audio sub session
	MediaSubsession			*m_pAsPss;

	/// Left over packet data
	sqbind::CSqBinary		m_buf;

	/// Extra video codec data
	sqbind::CSqBinary		m_extraVideo;

	/// Extra audio codec data
	sqbind::CSqBinary		m_extraAudio;

	/// Number of frames that have been processed
	int						m_nFrames;

	/// Video frame width
	int						m_width;

	/// Video frame height
	int						m_height;

	/// Video frame height
	int						m_fps;

	/// Signal to start RTSP stream
	oexEvent				m_evtPlay;

	/// SDP string
	sqbind::CSqMulti		m_mSdp;

};
