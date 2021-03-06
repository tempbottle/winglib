/*------------------------------------------------------------------
// memory.h
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

/*
                   ~;
                  ,/|\,
                ,/' |\ \,
              ,/'   | |  \
            ,/'     | |   |
          ,/'       |/    |
        ,/__________|-----' ,
       ___.....-----''-----/
       \                  /
   ~~-~^~^~`~^~`~^^~^~-^~^~^~-~^~^
     ~-^~^-`~^~-^~^`^~^-^~^`^~^-~^
*/

#pragma once

/// Generic memory allocator
/**
    Memory allocator.  Transparently supports heap and file mapping.

    \warning When using shared memory, constructors are called only
             when the memory block is created.  The destructor is
             called when the memory is actually freed.  If your
             sharing memory between processes, this means the
             constructor may be called in one process, and the
             destructor in another.  So plan accordingly!
*/
template < typename T, typename T_AS = T > class TMem
{
public:

	typedef oexSIZE_T		t_size;


public:

    TMem()
    {
        m_pMem = oexNULL;

#if defined ( oexDEBUG )
        m_pBh = oexNULL;
#endif

#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
        m_pFile = oexNULL;
        m_uLine = 0;
#endif
    }

    TMem( T* x_pMem, oexBOOL x_bConstructed = oexTRUE )
    {
        m_pMem = x_pMem;

#if defined ( oexDEBUG )
        if ( m_pMem )
            m_pBh = oexNULL;
        else
            m_pBh = CAlloc::GetBlockHeader( m_pMem );
#endif

#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
        m_pFile = oexNULL;
        m_uLine = 0;
#endif
    }

    TMem( oexCONST T& x_rMem, oexBOOL x_bConstructed = oexTRUE )
    {
        m_pMem = oexNULL;

#if defined ( oexDEBUG )
        m_pBh = oexNULL;
#endif

#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
        m_pFile = oexNULL;
        m_uLine = 0;
#endif
        // Construct a copy
        *this = x_rMem;
    }

    TMem( oexCONST TMem &x_m )
    {
        m_pMem = oexNULL;

#if defined ( oexDEBUG )
        m_pBh = oexNULL;
#endif

#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
        m_pFile = oexNULL;
        m_uLine = 0;
#endif
        // Just share the memory
        Share( x_m );
    }

    /// Copy operator
    TMem& operator = ( oexCONST TMem &x_m )
    {
        return Share( x_m );
    }

    /// Copy operator
    TMem& operator = ( oexCONST T &x_rObj )
    {
        OexConstruct();

        if ( Ptr() )
            *Ptr() = x_rObj;

        return *this;
    }

	/// Destructor
    virtual ~TMem()
    {
        Delete();
    }

	/// Releases the memory.
	// This is just a standard function for me ;)
    void Destroy()
    {
    	Delete();
	}

	/// Returns non-zero if there is a valid memory pointer
	oexBOOL IsValid()
	{	return ( oexNULL != Ptr() ); }

    /// Sets the shared memory name
    /**
        \param [in] x_pName -   Shared memory name
        \param [in] x_uLen  -   Length of the string in x_pName.
                                Can be zero if the string is
                                NULL terminated.

    */
    TMem& SetName( oexCSTR x_pName, t_size x_uLen = 0 )
    {   m_fm.SetName( x_pName, x_uLen );
        return *this;
    }

	/// Returns the shared name
	oexCSTR GetName()
	{	return m_fm.GetName(); }

	/// Sets a file handle for shared memory
    TMem& SetShareHandle( os::CFMap::t_HFILEMAP x_hHandle )
    {  	m_fm.SetShareHandle( x_hHandle );
    	return *this;
	}

	/// Returns the shared file handle
	os::CFMap::t_HFILEMAP GetShareHandle()
	{	return m_fm.GetShareHandle(); }

    /// Detaches from memory pointer
    /**
        You can't detach from a shared memory pointer using this function!
    */
    T* Detach()
    {   T* pPtr = m_pMem;
        m_pMem = oexNULL;
        return pPtr;
    }

    /// Returns non-zero if memory mapping is being used
    oexBOOL IsMapped() const
    {   return 0 < m_fm.Size(); }

	/// Allocate a new block of memory
    TMem& New( t_size x_uSize, oexBOOL x_bConstructed = oexFALSE, oexBOOL x_bUseFullBlock = oexFALSE )
    {
        // Lose old memory
        Delete();

        // Shared memory?
        if ( m_fm.GetName() || m_fm.IsShareHandle() )

            // Create memory mapping
            m_fm.Create( x_bConstructed, oexNULL, oexNULL, oexNULL, x_uSize );

        // Allocate plain old memory
        else
#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
            m_pMem = CAlloc( m_uLine, m_pFile ).New< T >( x_uSize, x_bConstructed, x_bUseFullBlock );
            m_pFile = oexNULL;
            m_uLine = 0;
#else
            m_pMem = CAlloc().New< T >( x_uSize, x_bConstructed, x_bUseFullBlock );
#endif

#if defined ( oexDEBUG )
        if ( !Ptr() || IsPlainShare() )
            m_pBh = oexNULL;
        else
            m_pBh = CAlloc::GetBlockHeader( Ptr() );
#endif
        return *this;
    }

    t_size Size() const
    {
        oexCONST T *pPtr = nc_Ptr();

        if ( !pPtr )
            return 0;

		if ( m_fm.c_Ptr() && IsPlainShare() )
			return m_fm.Size();
        else if ( sizeof( T ) )
            return CAlloc().ArraySize( pPtr );
        else
            return 0;
    }

	t_size SizeInBytes() const
	{
		return Size() * sizeof( T );
	}

    /// Returns non-zero if the object was constructed
    oexBOOL IsConstructed() const
    {   if ( m_fm.c_Ptr() && IsPlainShare() ) return 0;
		return ( CAlloc::eF1Constructed & CAlloc::GetFlags( c_Ptr() ) ) ? oexTRUE : oexFALSE;
    }

    /// Deletes the object
    void Delete()
    {
        // Allocation?
        if ( m_pMem )
        {
            // Free the memory
#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
            CAlloc( m_uLine, m_pFile ).Delete( m_pMem );
#else
            CAlloc().Delete( m_pMem );
#endif
            // Lose the pointer
            m_pMem = oexNULL;

        } // end if

        // Lose file mapping if any
        if ( m_fm.Ptr() )
            m_fm.Destroy();
    }

    void Destruct()
    {
		if ( !IsPlainShare() )
			CAlloc::SetFlags( m_pMem, CAlloc::eF1Constructed | CAlloc::GetFlags( m_pMem ) );
        Delete();
    }

	/// Zero memory
    TMem& Zero()
    {
        t_size uSize = Size();
        if ( !m_pMem || !uSize )
			return *this;

        // Constructed?
        if ( CAlloc::eF1Constructed & CAlloc::GetFlags( m_pMem ) )

			// For each element
            for ( t_size i = 0; i < uSize; i++ )

	            // Set to new object
				*Ptr( i ) = T_AS();

        // Just copy POD
        else
            oexZeroMemory( m_pMem, uSize * sizeof( T ) );

		return *this;
	}

    /// Generic resize
    TMem& Resize( t_size x_uNewSize )
    {
        // Shared memory cannot be resized
        if ( !oexVERIFY( !m_fm.Ptr() ) )
            return *this;

		// Unshare the memory
		Unshare();

        // Do we have what we need?
        t_size uSize = Size();
        if ( uSize == x_uNewSize )
            return *this;

        // Anything to resize?
        if ( !m_pMem )
            return New( x_uNewSize );

		// Can only do an inplace resize on simple types
		// because if it moves, all the contained pointers will
		// be screwed up.
		oexBOOL bAllowMove = ( 0 == ( CAlloc::eF1Constructed & CAlloc::GetFlags( m_pMem ) ) );

        // If we're shrinking
        if ( x_uNewSize < uSize )
        {
            // Was the object constructed?
            if ( CAlloc::eF1Constructed & CAlloc::GetFlags( m_pMem ) )
                for ( t_size i = x_uNewSize; i < uSize; i++ )
                    m_pMem[ i ].~T();

            // We can make things smaller
#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
            m_pMem = CAlloc( m_uLine, m_pFile ).Resize( m_pMem, x_uNewSize, bAllowMove );
#else
            m_pMem = CAlloc().Resize( m_pMem, x_uNewSize, bAllowMove );
#endif

        } // end if

        // We must be making it larger
        else
        {
			T* pMem = oexNULL;

#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
	        pMem = CAlloc( m_uLine, m_pFile ).Resize( m_pMem, x_uNewSize, bAllowMove );
#else
    	    pMem = CAlloc().Resize( m_pMem, x_uNewSize, bAllowMove );
#endif

			// Do we have new memory?
            if ( !pMem )
            {
                TMem< T > mem;
#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
                if ( !oexVERIFY_PTR( mem._Log( m_uLine, m_pFile ).New( x_uNewSize ).Ptr() ) )
#else
                if ( !oexVERIFY_PTR( mem.New( x_uNewSize ).Ptr() ) )
#endif
                    return *this;

                // Constructed?
                if ( CAlloc::eF1Constructed & CAlloc::GetFlags( m_pMem ) )
                {
                    // Initialize new array
                    for ( t_size i = 0; i < x_uNewSize; i++ )

                        if ( i < uSize )
                            *mem.Ptr() = *Ptr();
                        else
                            oexPLACEMENT_NEW ( mem.Ptr( i ) ) T();

                } // end if

                // Just copy POD
                else
                    os::CSys::MemCpy( mem.Ptr(), Ptr(), uSize * sizeof( T ) );

                // Assume this new array
                Assume( mem );

            } // end if

            // If the memory moved
            else
            {
				// Save new memory location
				m_pMem = pMem;

				// Initialize the new objects
				if ( CAlloc::eF1Constructed & CAlloc::GetFlags( m_pMem ) )
					for ( t_size i = uSize; i < x_uNewSize; i++ )
						oexPLACEMENT_NEW ( &pMem[ i ] ) T();

			} // end else

        } // end else

#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )
        m_pFile = oexNULL;
        m_uLine = 0;
#endif

        return *this;
    }

    /// Returns pointer to the memory
    T_AS* operator ->()
    {   return Ptr(); }

    /// Returns pointer to the memory
    T_AS* operator *()
    {   return Ptr(); }

	//==============================================================
	// n_Ptr()
	//==============================================================
	/// Returns a pointer to the memory
    T* n_Ptr()
    {
        if ( m_pMem )
            return m_pMem;

        return m_fm.Ptr();
    }

	//==============================================================
	// n_Ptr()
	//==============================================================
	/// Returns a pointer to the memory
    /**
        \param [in] x_uOffset   -   Offset into the memory
    */
    T* n_Ptr( t_size x_uOffset )
    {
        T* pPtr = n_Ptr();

        if ( !pPtr )
            return oexNULL;

        // Out of bounds
        oexASSERT( Size() > x_uOffset );

        return &pPtr[ x_uOffset ];
    }

	//==============================================================
	// nc_Ptr()
	//==============================================================
	/// Returns a pointer to the memory
    oexCONST T* nc_Ptr() const
    {
        if ( m_pMem )
            return m_pMem;

        return m_fm.c_Ptr();
    }

	//==============================================================
	// nc_Ptr()
	//==============================================================
	/// Returns a pointer to the memory
    /**
        \param [in] x_uOffset   -   Offset into the memory
    */
    oexCONST T* nc_Ptr( t_size x_uOffset ) const
    {
        oexCONST T* pPtr = nc_Ptr();

        if ( !pPtr )
            return oexNULL;

        // Out of bounds
        oexASSERT( Size() > x_uOffset );

        return &pPtr[ x_uOffset ];
    }


	//==============================================================
	// Ptr()
	//==============================================================
	/// Returns a pointer to the memory
    T_AS* Ptr()
    {
        if ( m_pMem )
            return (T_AS*)m_pMem;

        return (T_AS*)m_fm.Ptr();
    }

	//==============================================================
	// Ptr()
	//==============================================================
	/// Returns a pointer to the memory
    /**
        \param [in] x_uOffset   -   Offset into the memory
    */
    T_AS* Ptr( t_size x_uOffset )
    {
        T_AS* pPtr = Ptr();

        if ( !pPtr )
            return oexNULL;

        // Out of bounds
#if defined( oexDEBUG )
		if ( !IsPlainShare() )
			oexASSERT( ( Size() * sizeof( T_AS ) / sizeof( T ) ) > x_uOffset );
#endif

        return &pPtr[ x_uOffset ];
    }

	//==============================================================
	// c_Ptr()
	//==============================================================
	/// Returns a pointer to the memory
	oexCONST T_AS* c_Ptr() const
    {
        if ( m_pMem )
            return (T_AS*)m_pMem;

        return (T_AS*)m_fm.c_Ptr();
    }

	//==============================================================
	// c_Ptr()
	//==============================================================
	/// Returns a pointer to the memory
    /**
        \param [in] x_uOffset   -   Offset into the memory
    */
    oexCONST T_AS* c_Ptr( t_size x_uOffset ) const
    {
        oexCONST T_AS* pPtr = c_Ptr();

        if ( !pPtr )
            return oexNULL;

        // Out of bounds
#if defined( oexDEBUG )
		if ( !IsPlainShare() )
			oexASSERT( ( Size() * sizeof( T_AS ) / sizeof( T ) ) > x_uOffset );
#endif

        return &pPtr[ x_uOffset ];
    }

	//==============================================================
	// Ptr()
	//==============================================================
	/// Returns a reference to the element
    /**
        I didn't want to provide this function since it is so easy
        to abuse.  You should really make sure the index exists
        before you call this function.
    */
    T_AS& operator [] ( t_size x_uOffset )
    {
        // Ensure index
        if ( ( Size() * sizeof( T_AS ) / sizeof( T ) ) <= x_uOffset )
            Resize( x_uOffset * sizeof( T ) / sizeof( T_AS ) );

        // Really ensure
        if ( Size() * sizeof( T_AS ) / sizeof( T ) <= x_uOffset )
        {   oexASSERT( 0 );
            x_uOffset = 0;
        } // end if

        return *Ptr( x_uOffset );
    }

public:

    /// Adds a reference to the memory block
    t_size AddRef()
    {   if ( !Ptr() ) return 0;
        return CAlloc().AddRef( Ptr() );
    }

    /// Returns the memory blocks reference count
    t_size GetRefCount()
    {   if ( !Ptr() ) return 0;
        return CAlloc().GetRefCount( Ptr() );
    }

    /// Assumes control of another objects data
    TMem& Assume( TMem &x_m )
    {
        // Drop current
        Delete();

        // Assume the memory from this object
        if ( x_m.m_pMem )
        {   m_pMem = x_m.m_pMem; x_m.m_pMem = oexNULL;
            m_fm = x_m.m_fm; x_m.m_fm.Detach();
        } // end if

#if defined ( oexDEBUG )
        if ( !Ptr() )
            m_pBh = oexNULL;
        else
            m_pBh = CAlloc::GetBlockHeader( Ptr() );
#endif
        return *this;
    }

    /// Copy data from a raw buffer
    TMem& MemCpy( oexCONST T *x_pBuf, t_size x_uSize )
    {
        // Verify pointer
        if ( !oexVERIFY_PTR( x_pBuf ) || !x_uSize )
            return *this;

        // Do we need more space?
        if ( Size() < x_uSize )
            if ( !OexNew( x_uSize ).Ptr() )
                return *this;

        // Copy data if all the stars align
        os::CSys::MemCpy( Ptr(), x_pBuf, x_uSize * sizeof( T ) );

        return *this;
    }

    /// Append data from a raw buffer
    TMem& MemAppend( oexCONST T *x_pBuf, t_size x_uSize )
    {
        // Verify pointer
        if ( !oexVERIFY_PTR( x_pBuf ) || !x_uSize )
            return *this;

		// How much space do we need?
		t_size uSize = Size();
		t_size uNewSize = uSize + x_uSize;

        // Do we need more space?
        if ( uSize < uNewSize )
            if ( !OexResize( uNewSize ).Ptr() )
                return *this;

        // Copy data if all the stars align
        os::CSys::MemCpy( Ptr( uSize ), x_pBuf, x_uSize * sizeof( T ) );

        return *this;
    }

    /// Append data from a raw buffer
    TMem& MemCpyAt( oexCONST T *x_pBuf, t_size x_uPos, t_size x_uSize )
    {
        // Verify pointer
        if ( !oexVERIFY_PTR( x_pBuf ) || !x_uSize )
            return *this;

		// How much space do we need?
		t_size uSize = Size();
		t_size uNewSize = x_uPos + x_uSize;

        // Do we need more space?
        if ( uSize < uNewSize )
            if ( !OexResize( uNewSize ).Ptr() )
                return *this;

        // Copy data if all the stars align
        os::CSys::MemCpy( Ptr( x_uPos ), x_pBuf, x_uSize * sizeof( T ) );

        return *this;
    }

    /// Copy data from a raw buffer
    t_size getCpy( T *x_pBuf, t_size x_uSize )
    {
        // Verify pointer
        if ( !oexVERIFY_PTR( x_pBuf ) || !x_uSize )
            return 0;

        // Is there that much data?
        if ( Size() < x_uSize )
        	x_uSize = Size();

        // Copy data if all the stars align
        os::CSys::MemCpy( x_pBuf, Ptr(), x_uSize * sizeof( T ) );

        return x_uSize;
    }

    /// Append data from a raw buffer
    t_size getCpyAt( T *x_pBuf, t_size x_uPos, t_size x_uSize )
    {
        // Verify pointer
        if ( !oexVERIFY_PTR( x_pBuf ) || !x_uSize )
            return 0;

		// Anything to copy
		t_size uSize = Size();
		if ( x_uPos >= uSize )
			return 0;

		// Amount of space available
		uSize -= x_uPos;
		if ( x_uSize > uSize )
			x_uSize = uSize;

        // Copy data if all the stars align
        os::CSys::MemCpy( x_pBuf, Ptr( x_uPos ), x_uSize * sizeof( T ) );

        return x_uSize;
    }

	/// Removes data from the beginning of the buffer
	//  Not efficient
    TMem& LShift( t_size x_uPos, t_size x_uSize )
    {
        // Verify pointer
        if ( !x_uSize )
            return *this;

		t_size uSize = Size();

		// Valid?
		if ( x_uPos >= uSize )
			return *this;

		// Whole buffer?
		if ( !x_uSize )
			x_uSize = uSize - x_uPos;

		// Ensure reasonable size
		if ( ( x_uPos + x_uSize ) > uSize )
			x_uSize = uSize - x_uPos;

		// Move the data
        os::CSys::MemCpy( Ptr(), Ptr( x_uPos ), x_uSize );

        return *this;
    }

    /// Copies another objects data
    TMem& Copy( oexCONST TMem &x_m, oexCSTR x_pNewName = oexNULL, t_size x_uNameLen = 0 )
    {
        // Drop current
        Delete();

        // Raw memory?
        if ( x_m.m_pMem || ( x_pNewName && *x_pNewName ) )
        {
            t_size uSize = x_m.Size();
            if ( uSize )
            {
                // Shared memory?
                if ( x_pNewName && *x_pNewName )
                    SetName( x_pNewName, x_uNameLen );

                // Do we need to construct objects?
                if ( x_m.IsConstructed() )
                {
                    // Create array of objects
                    OexConstructArray( uSize );

                    // Copy objects
                    // +++ Casting away const
                    for ( t_size i = 0; i < uSize; i++ )
                        *Ptr( i ) = *(T*)( x_m.c_Ptr( i ) );

                } // end if

                else
                {
                    // Allocate raw array
                    OexNew( uSize );

                    // Just copy the memory
                    os::CSys::MemCpy( Ptr(), x_m.c_Ptr(), uSize * sizeof( T ) );

                } // end else

            } // end if

        } // end if

        // Copy shared memory
        else if ( x_m.m_fm.c_Ptr() )
            m_fm.Copy( x_m.m_fm );

        return *this;
    }

    /// Returns a copy of this object
    TMem Copy( oexCSTR x_pNewName = oexNULL, t_size x_uNameLen = 0 )
    {   TMem mem;
        if ( Ptr() )
            mem.Copy( *this, x_pNewName, x_uNameLen );
        return mem;
    }

    /// Creates our own copy of a string if it's shared
	oexBOOL Unshare()
	{
		// Punt if not shared or offset
		if ( 1 == GetRefCount() )
			return oexTRUE;

		// Create a new buffer
		TMem< T > mem;
		if ( !oexVERIFY_PTR( mem.OexNew( Size() ).Ptr() ) )
			return oexFALSE;

		// Copy our buffer
		mem.Copy( *this );

        // Use the new memory
		Assume( mem );

		return oexTRUE;
	}

    /// Causes this object to share memory with another
    TMem& Share( oexCONST TMem &x_m )
    {
        Delete();

        // Is it memory mapped, different kind of share ;)
        if ( x_m.IsMapped() )
            Copy( x_m );

        // Just add a reference to the memory
        else if ( x_m.m_pMem )
            CAlloc().AddRef( ( m_pMem = x_m.m_pMem ) );

#if defined ( oexDEBUG )
        if ( !Ptr() )
            m_pBh = oexNULL;
        else
            m_pBh = CAlloc::GetBlockHeader( Ptr() );
#endif
        return *this;
    }

    /// Causes this object to share memory with another
    TMem& Share( oexCONST T *x_pMem )
    {
        // Lose old memory
        Delete();

        // Share this memory pointer
        if ( x_pMem )
            CAlloc().AddRef( ( m_pMem = (T*)x_pMem ) );

#if defined ( oexDEBUG )
        if ( !Ptr() )
            m_pBh = oexNULL;
        else
            m_pBh = CAlloc::GetBlockHeader( Ptr() );
#endif
        return *this;
    }

public:

    /// Construct object
    TMem& Construct()
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T();

        return *this;
    }

    /// Construct object
    template< typename T_P1 >
        TMem& Construct( T_P1 p1 )
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T( p1 );

        return *this;
    }

    /// Construct object, 2 params
    template< typename T_P1, typename T_P2 >
        TMem& Construct( T_P1 p1, T_P2 p2 )
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T( p1, p2 );

        return *this;
    }

    /// Construct object, 3 params
    template< typename T_P1, typename T_P2, typename T_P3 >
        TMem& Construct( T_P1 p1, T_P2 p2, T_P3 p3 )
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T( p1, p2, p3 );

        return *this;
    }

    /// Construct object, 4 params
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4 >
        TMem& Construct( T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4 )
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T( p1, p2, p3, p4 );

        return *this;
    }

    /// Construct object, 5 params
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4, typename T_P5 >
        TMem& Construct( T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4, T_P5 p5 )
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T( p1, p2, p3, p4, p5 );

        return *this;
    }

    /// Construct object, 6 params
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4, typename T_P5, typename T_P6 >
        TMem& Construct( T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4, T_P5 p5, T_P6 p6 )
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T( p1, p2, p3, p4, p5, p6 );

        return *this;
    }

    /// Construct object, 7 params
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4, typename T_P5, typename T_P6, typename T_P7 >
        TMem& Construct( T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4, T_P5 p5, T_P6 p6, T_P7 p7 )
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T( p1, p2, p3, p4, p5, p6, p7 );

        return *this;
    }

    /// Construct object, 8 params
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4, typename T_P5, typename T_P6, typename T_P7, typename T_P8 >
        TMem& Construct( T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4, T_P5 p5, T_P6 p6, T_P7 p7, T_P8 p8 )
    {
        T* p = New( 1, oexTRUE ).Ptr();
        if ( m_pMem || !m_fm.Existing() )
            oexPLACEMENT_NEW ( p ) T( p1, p2, p3, p4, p5, p6, p7, p8 );

        return *this;
    }

public:

    /// Construct object array
    TMem& ConstructArray( t_size x_uSize )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T();

        return *this;
    }

    /// Construct object array, 1 param
    template< typename T_P1 >
        TMem& ConstructArray( t_size x_uSize, T_P1 p1 )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T( p1 );

        return *this;
    }

    /// Construct object array, 2 param
    template< typename T_P1, typename T_P2 >
        TMem& ConstructArray( t_size x_uSize, T_P1 p1, T_P2 p2 )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T( p1, p2 );

        return *this;
    }

    /// Construct object array, 3 param
    template< typename T_P1, typename T_P2, typename T_P3 >
        TMem& ConstructArray( t_size x_uSize, T_P1 p1, T_P2 p2, T_P3 p3 )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T( p1, p2, p3 );

        return *this;
    }

    /// Construct object array, 4 param
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4 >
        TMem& ConstructArray( t_size x_uSize, T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4 )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T( p1, p2, p3, p4 );

        return *this;
    }

    /// Construct object array, 5 param
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4, typename T_P5 >
        TMem& ConstructArray( t_size x_uSize, T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4, T_P5 p5 )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T( p1, p2, p3, p4, p5 );

        return *this;
    }

    /// Construct object array, 6 param
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4, typename T_P5, typename T_P6 >
        TMem& ConstructArray( t_size x_uSize, T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4, T_P5 p5, T_P6 p6 )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T( p1, p2, p3, p4, p5, p6 );

        return *this;
    }

    /// Construct object array, 7 param
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4, typename T_P5, typename T_P6, typename T_P7 >
        TMem& ConstructArray( t_size x_uSize, T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4, T_P5 p5, T_P6 p6, T_P7 p7 )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T( p1, p2, p3, p4, p5, p6, p7 );

        return *this;
    }

    /// Construct object array, 8 param
    template< typename T_P1, typename T_P2, typename T_P3, typename T_P4, typename T_P5, typename T_P6, typename T_P7, typename T_P8 >
        TMem& ConstructArray( t_size x_uSize, T_P1 p1, T_P2 p2, T_P3 p3, T_P4 p4, T_P5 p5, T_P6 p6, T_P7 p7, T_P8 p8 )
    {
        T *p = New( x_uSize, oexTRUE ).Ptr();
        if ( oexVERIFY( p ) && ( m_pMem || !m_fm.Existing() ) )
            for ( t_size i = 0; i < x_uSize; i++ )
                oexPLACEMENT_NEW ( &p[ i ] ) T( p1, p2, p3, p4, p5, p6, p7, p8 );

        return *this;
    }

	/// Enables plain share mode
	void PlainShare( oexBOOL x_bPlain )
	{	m_fm.Plain( x_bPlain ); }

	/// Returns non-zero if plain share
	oexBOOL IsPlainShare() const
	{	return m_fm.IsPlain(); }

	/// Sets the file mapping segment offset
	void SetOffset( oexINT64 x_llOffset )
	{	m_fm.SetOffset( x_llOffset ); }

	/// Gets the file mapping segment offset
	oexINT64 GetOffset()
	{	return m_fm.GetOffset(); }

	/// Returns Non-zero if file mapping already existed
	oexBOOL Existing()
	{	return m_fm.Ptr() && m_fm.Existing(); }

private:

    /// Pointer to the memory
	union
	{
		T*                      m_pMem;
		T_AS*					m_pMemAs;
	};

    /// File mapping object for shared memory
    TFileMapping< T >       m_fm;

#if defined( oexDEBUG )

    /// This is pulled out in the debug version just for debugging
    CAlloc::SBlockHeader    *m_pBh;

#endif

#if defined( oexDEBUG ) || defined( OEX_ENABLE_RELEASE_MODE_MEM_CHECK )

public:

    /// Registers the source file and line number
    TMem& _Log( oexUINT x_uLine, oexCSTR x_pFile )
    {   m_uLine = x_uLine;
        m_pFile = x_pFile;
        return *this;
    }

private:

    /// Holds the line number of the allocating call
    oexUINT         m_uLine;

    /// Holds the file name of the allocating call
    oexCSTR         m_pFile;

#endif

};
