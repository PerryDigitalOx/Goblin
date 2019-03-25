// seems to support only Intel Indeo codecs.

#include <CDX.h>
#include <stdexcpt.h>
#include "avisurface.h"

#define DDSD_STANDARTINIT(a) ZeroMemory(&a,sizeof(a));a.dwSize=sizeof(a)

CAviSurface::CAviSurface(char *lpszFilename,LPDIRECTDRAW4 lpDDraw,BOOL bLoop)
{
	// Initialize the AVI - Interface
	AVIFileInit();
    // Set looping
	m_bLoop = bLoop;
	// Set standart values
	m_lIndex = 0;
	m_lpAviSurface = 0;
	m_pasMovie = 0;
	ZeroMemory(&m_asiMovie,sizeof(m_asiMovie));
	m_lIndex = m_lFrames = 0;
	m_hicDecompressor = 0;
	m_lpInput=m_lpOutput = 0;
    // Open the VIDEO-Part of AVI File
	if (AVIStreamOpenFromFile(&m_pasMovie,lpszFilename,streamtypeVIDEO,0,OF_READ,NULL)) {
		// failture - Exit AVI-Interface
		AVIFileExit();
		// Jump out of constructor with exception
		throw exception("AVI-File not found");
	}
	// Standartvalues for Colorkeying
	m_dwColorKeyFlagFast = DDBLTFAST_NOCOLORKEY;
	// Currently no Colorkey
	m_dwColorKeyFlag = 0;
	// Try to init the AVI-File
	if (!Init(lpDDraw))	{
		// Close on failture
		Close();
		// Jump out of constructor with exception
		throw exception("AVI Init failed");
	}
	// Init the critical section for accessing buffers
	InitializeCriticalSection(&m_csAccessBuffer);
}

CAviSurface::~CAviSurface()
{
	// Stop playing
	Stop();
	// Destroy critical section
	DeleteCriticalSection(&m_csAccessBuffer);
	// Close AVI-File
	Close();
	// Exit AVI-Interface
	AVIFileExit();
}

bool CAviSurface::Init(LPDIRECTDRAW4 lpDDraw)
{
	LONG lFmtLenght;
	DDSURFACEDESC2 ddsd;
	int ddrval;

	// Get Graphicformat length from AVI
	AVIStreamFormatSize(m_pasMovie,0,&lFmtLenght);
	// Allocate Memory for Sourceformatinfo
	m_lpScrFmt = (LPBITMAPINFOHEADER)malloc(lFmtLenght);
	//  Allocate Memory for Targetformatinfo
	m_lpb4hTargetFmt = (LPBITMAPV4HEADER)malloc(max(lFmtLenght,sizeof(BITMAPV4HEADER)));
	// Zero out the target format area
	ZeroMemory(m_lpb4hTargetFmt,sizeof(BITMAPV4HEADER));
	// Get the Graphicformat
	AVIStreamReadFormat(m_pasMovie,0,m_lpScrFmt,&lFmtLenght);
	// Get the count of frames of the video
	m_lFrames = AVIStreamLength(m_pasMovie);
	// Get additional video-info
	AVIStreamInfo(m_pasMovie,&m_asiMovie,sizeof(AVISTREAMINFO));

	// Zero out the structure and set the size of the structure
	DDSD_STANDARTINIT(ddsd);
	// Set the surface description of the AVI-Buffer
	ddsd.dwWidth = m_lpScrFmt->biWidth;
    ddsd.dwHeight  = m_lpScrFmt->biHeight;
	ddsd.dwFlags = DDSD_WIDTH|DDSD_HEIGHT|DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_TEXTURE|DDSCAPS_SYSTEMMEMORY;

	// Create the Buffer
    ddrval=lpDDraw->CreateSurface(&ddsd,&m_lpAviSurface,0);
	// Creation failed
	if (ddrval!=DD_OK){
		// Exit the Init with a failture
		return false;
	}
    // Get the full description of the surface
	m_lpAviSurface->GetSurfaceDesc(&ddsd);
    // copy the src-Format to the target format
	memcpy(m_lpb4hTargetFmt,m_lpScrFmt,lFmtLenght);
    // Set targetformatsize to correct length
	m_lpb4hTargetFmt->bV4Size = max(lFmtLenght,sizeof(BITMAPV4HEADER));
	// Set the target bitcount
	m_lpb4hTargetFmt->bV4BitCount = ddsd.ddpfPixelFormat.dwRGBBitCount;

	// if you want to support 8-bit colordepth targetsurfaces you will have to change
	// this part of the source

	// Setup the color-translation
	m_lpb4hTargetFmt->bV4V4Compression = BI_BITFIELDS;
    // we only support Hi and truecolor in
	if (m_lpb4hTargetFmt->bV4BitCount==24) {
		// this example
		m_lpb4hTargetFmt->bV4V4Compression = BI_RGB;
	}
	// no RGB-Table
    m_lpb4hTargetFmt->bV4ClrUsed = 0;
	// Red mask
	m_lpb4hTargetFmt->bV4RedMask   = ddsd.ddpfPixelFormat.dwRBitMask;
	// Green mask
    m_lpb4hTargetFmt->bV4GreenMask = ddsd.ddpfPixelFormat.dwGBitMask;
	// Blue mask
    m_lpb4hTargetFmt->bV4BlueMask  = ddsd.ddpfPixelFormat.dwBBitMask;
	// Alpha mask
    m_lpb4hTargetFmt->bV4AlphaMask = ddsd.ddpfPixelFormat.dwRGBAlphaBitMask;
	// Size of image
	m_lpb4hTargetFmt->bV4SizeImage =
		   ((m_lpb4hTargetFmt->bV4Width +3)&0xFFFFFFFC) *
		     m_lpb4hTargetFmt->bV4Height *
			   (m_lpb4hTargetFmt->bV4BitCount>>3);
   // End of color transitition


    // Calculate length of a chunk
	m_lLength = m_lpScrFmt->biWidth *
		        m_lpScrFmt->biHeight *
				(m_lpScrFmt->biBitCount >> 3);


	// if there is a suggested buffersize
	if (m_asiMovie.dwSuggestedBufferSize){
		 // then use it
		 m_lLength = (LONG)m_asiMovie.dwSuggestedBufferSize;
	}
	// create the decompressor for the combination of source and target format
	m_hicDecompressor = ICDecompressOpen(ICTYPE_VIDEO,
		      m_asiMovie.fccHandler,m_lpScrFmt,
			        (LPBITMAPINFOHEADER)m_lpb4hTargetFmt);

	// No decompressor available ?
	if (!m_hicDecompressor)	{
		// exit with a failture
		return FALSE;
	}

	// Create Inputbuffer with suggested size
	m_lpInput = (BYTE *)calloc(m_lLength,1);
	// empty it
	ZeroMemory(m_lpInput,m_lLength);

	// Create the targetbuffer of the decompressor
	m_lpOutput = (BYTE *)calloc(m_lpb4hTargetFmt->bV4SizeImage,1);
    // Zero it out
	ZeroMemory(m_lpOutput,m_lpb4hTargetFmt->bV4SizeImage);
	// Calculate linepitch in decompressorbuffer
	m_lLinePitch = m_lpb4hTargetFmt->bV4Width * (m_lpb4hTargetFmt->bV4BitCount>>3);
	// Open the decompressor
	ICDecompressBegin(m_hicDecompressor,m_lpScrFmt,(LPBITMAPINFOHEADER)m_lpb4hTargetFmt);
	// Calculate framerate
    m_dwFps = (m_asiMovie.dwRate+(m_asiMovie.dwScale>>1))/m_asiMovie.dwScale;
	// time between two frames in x ms (needed for the timer)

	m_iTimeTick = (1000*m_asiMovie.dwScale+(m_asiMovie.dwRate>>1))/m_asiMovie.dwRate;

	// Create Sourcerect.
	m_rcSrc.left= 0;
	m_rcSrc.top = 0;
	m_rcSrc.right = m_lpb4hTargetFmt->bV4Width;
	m_rcSrc.bottom = m_lpb4hTargetFmt->bV4Height;

	// Success!
	return true;
}

void CAviSurface::Close()
{
	// End and close Decompressor
	if (m_hicDecompressor)	{
	  ICDecompressEnd(m_hicDecompressor);
	  ICClose(m_hicDecompressor);
	}

	// Release Surface
	if (m_lpAviSurface)
       m_lpAviSurface->Release();

	// Free all allocated mem
	if (m_lpScrFmt)       free(m_lpScrFmt);
	if (m_lpb4hTargetFmt) free(m_lpb4hTargetFmt);
	if (m_lpInput)        free(m_lpInput);
	if (m_lpOutput)       free(m_lpOutput);

	// Release Video stream
	AVIStreamRelease(m_pasMovie);
}

void CAviSurface::GetNextFrame()
{

	if (m_lIndex==m_lFrames) {  // we have reached the end  ?
		if (m_bLoop)            // we are looping ?
		  m_lIndex = 0;         // yes
		else {
		  m_bRunning = false;   // no
		  timeKillEvent(m_iTimerID); // so kill the timeevent
		  return;
		}
    }
	ReadFrame(m_lIndex);        // Read AVI - Info
	m_lIndex++;                 // count up frame index
}

HRESULT CAviSurface::BlitTo(int x,int y,LPDIRECTDRAWSURFACE4 lpddsTarget)
{
	HRESULT ddrval;

	// Draw the decompressorbuffer to the surface
	if ((ddrval = DrawBuffer())!=DD_OK)
		return ddrval;

	// Blit the DDS to the targetsurface
	return lpddsTarget->BltFast(x,y,m_lpAviSurface,&m_rcSrc,
		                     m_dwColorKeyFlagFast|DDBLTFAST_WAIT);
}


HRESULT CAviSurface::StretchBlitTo(RECT *rcTarget,LPDIRECTDRAWSURFACE4 lpddsTarget)
{
	HRESULT ddrval;
	// Draw the decompressorbuffer to the surface
	if ((ddrval = DrawBuffer())!=DD_OK)
		return ddrval;

	// Blit the DDS to the targetsurface
    return  lpddsTarget->Blt(rcTarget,m_lpAviSurface,&m_rcSrc,
		      m_dwColorKeyFlag|DDBLT_WAIT,NULL);
}

static void CALLBACK GetFrameTimeProc(UINT, UINT, DWORD dwAviSurface, DWORD, DWORD)
{
	// if AVI not  running then exit
	if (!((CAviSurface *)dwAviSurface)->m_bRunning)
		return;
	// else get the next frame
    ((CAviSurface *)dwAviSurface)->GetNextFrame();
}

bool CAviSurface::Start()
{
	// Init the timeevent
	m_iTimerID = timeSetEvent(m_iTimeTick,0,GetFrameTimeProc,(ULONG)this,TIME_PERIODIC);
	// timer running ?
	// this code will produce a warning "possibly incorrect assignment"
	if (m_bRunning = (m_iTimerID!=NULL)){
	  // Get the first frame
	  CAviSurface::ReadFrame(0);
	  //
	  m_lIndex++;                 // count up frame index
	}
	//
	return m_bRunning;
}

void CAviSurface::Stop()
{
	m_bRunning=false;          // no more running
	timeKillEvent(m_iTimerID); // kill the timerevent
	Sleep(m_iTimeTick+1);      // wait for pending timer event
}

HRESULT CAviSurface::DrawBuffer(void)
{
    DDSURFACEDESC2 ddsd;
	HRESULT ddrval;

	// Set size of structure
	ddsd.dwSize = sizeof(ddsd);
	// calculate startpointer of source
	LPBYTE lpbSRC = m_lpOutput + m_lLinePitch * (m_lpb4hTargetFmt->bV4Height-1);
	// Lock surface
	ddrval = m_lpAviSurface->Lock(NULL, &ddsd, DDLOCK_WAIT, NULL);
	// if lock success
	if( ddrval == DD_OK ) {
	    // get destinationpointer
	    LPBYTE lpDest =(LPBYTE)ddsd.lpSurface;
		// lock the decopressbuffer thread-save
		EnterCriticalSection(&m_csAccessBuffer);
		// copy decompression bottom up to top down to the DDS
        int y;
        for(y=0; y<(int)m_lpb4hTargetFmt->bV4Height;y++ ) {
			memcpy(lpDest, lpbSRC, m_lLinePitch);
			lpDest += ddsd.lPitch;
			lpbSRC -= m_lLinePitch;
		}
		// exit the critical section
		LeaveCriticalSection(&m_csAccessBuffer);
		// and unlock the Surface
		ddrval = m_lpAviSurface->Unlock(NULL);
	}
	// return the result
	return ddrval;
}

void CAviSurface::ReadFrame(DWORD dwFrame)
{
	// we are not at the end of the AVI
    if (dwFrame<m_lFrames) {
	  // Read the next frame from the video stream
	  AVIStreamRead(m_pasMovie, dwFrame, 1, m_lpInput, m_lLength, NULL, NULL);
	  // lock the decopressbuffer thread-save
	  EnterCriticalSection(&m_csAccessBuffer);
	  // decompress the frame
	  ICDecompress(m_hicDecompressor, 0, m_lpScrFmt, m_lpInput,
		  (LPBITMAPINFOHEADER)m_lpb4hTargetFmt, m_lpOutput);
	  // exit the critical section
	  LeaveCriticalSection(&m_csAccessBuffer);
	}
}

HRESULT CAviSurface::SetColorKey(DWORD dwColorKey)
{
	DDCOLORKEY ddck;
	// Set the colorkey low and high values
	ddck.dwColorSpaceLowValue = dwColorKey;
	ddck.dwColorSpaceHighValue = dwColorKey;
	// Set the blitting flag for BLTFAST
	m_dwColorKeyFlagFast = DDBLTFAST_SRCCOLORKEY;
	// Set the blitting flag for BLT
	m_dwColorKeyFlag = DDBLT_KEYSRC;
	// Set the key to the surface
	return m_lpAviSurface->SetColorKey(DDCKEY_SRCBLT,&ddck);
}

//CAviSurfaceWithSound::CAviSurfaceWithSound(char *lpszFilename,
//			      LPDIRECTDRAW2 lpDDraw,LPDIRECTSOUND lpDS,
//				       LPDIRECTSOUNDBUFFER lpdsPrimary,BOOL bLoop)
CAviSurfaceWithSound::CAviSurfaceWithSound(HWND hWnd, char *lpszFilename, LPDIRECTDRAW4 lpDDraw, BOOL bLoop)
	:CAviSurface(lpszFilename,lpDDraw,bLoop)
{
	m_AviWnd = hWnd;

    if(CreateSoundStuff() == false)
	{
		DestroySoundStuff();
		exception("CreateSoundStuff failed!");
	}

	// Set standartvalues
	ZeroMemory(&m_pasSound,sizeof(m_pasSound));
    m_lpSoundScrFmt = 0;
	m_lpdsbTon =0;
//	m_lpdsPrimary=lpdsPrimary;

	// Open sound stream
	if (AVIStreamOpenFromFile(&m_pasSound,lpszFilename,streamtypeAUDIO,0,OF_READ,NULL))
	{
		// Exit the AVIinterface
	    AVIFileExit();
		// Jump out with an exeption
		throw exception("Soundstream in AVI-File not found");
	}
	// currently no sound skew
	m_asiSound.dwInitialFrames = 0;

	// Try to init the soundpart
//	if (!InitSound(lpDS))
	if (!InitSound())
	{
		exception("InitSound failed for AVI-File");
	}
}

CAviSurfaceWithSound::~CAviSurfaceWithSound()
{
	CloseSound();
	DestroySoundStuff();
}

// Get the sound of the curent frame
void CAviSurfaceWithSound::GetFrameSound()
{
	DWORD dwSize1,dwSize2;
	void *Data1,*Data2;
	HRESULT dsrval;

    // Get pointer to soundbuffer
	dsrval = m_lpdsbTon->Lock(m_dwLoadPos*m_asiSound.dwSuggestedBufferSize,
		                m_asiSound.dwSuggestedBufferSize,
						&Data1,&dwSize1,&Data2,&dwSize2,0);

	if (dsrval!=DS_OK)
     		return;       // exit since Locking Soundbuffer failed


	// Read suggested buffersize Samples to DSB - since the soundbuferlength is
	// a multible of the m_asiSound.dwSuggestedBufferSize we dont have to worry about splitting
	// the loading
	AVIStreamRead(m_pasSound,m_lIndex*m_asiSound.dwSuggestedBufferSize/m_lpSoundScrFmt->nBlockAlign,
		                m_asiSound.dwSuggestedBufferSize/m_lpSoundScrFmt->nBlockAlign,Data1,m_asiSound.dwSuggestedBufferSize,NULL,NULL);

	// unlock the DSB
	dsrval=m_lpdsbTon->Unlock(Data1,dwSize1,Data2,dwSize2);

    // Adjust DSB Loadpos for next soundframe
	m_dwLoadPos++;
	m_dwLoadPos %= m_dwFps * 2;

}


void CAviSurfaceWithSound::GetNextFrame()
{
	if (m_lIndex==m_lFrames)
	{                                 // We are at the end of the AVI
		timeKillEvent(m_iTimerID);    // Kill the time event
		Sleep(m_iTimeTick+1);         // Wait for pending events
	    m_lpdsbTon->Stop();           // Stop soundplaying
		if (m_bLoop) {                // Are we looping?
          m_lIndex = 0;               // Reset index
		  m_dwLoadPos = 0;            // Reset loadpos
		  m_lpdsbTon->SetCurrentPosition(0);       // Reset Playpos
		  while (m_lIndex<m_asiSound.dwInitialFrames) {   // Load soundskew
			  GetFrameSound();
			  m_lIndex++;
		  }
		  // Start timer
		  m_iTimerID = timeSetEvent(m_iTimeTick,5,GetFrameTimeProc,(ULONG)this,TIME_PERIODIC);
		  // start playing sound
		  m_lpdsbTon->Play(0,0,DSBPLAY_LOOPING);
		}else{ // we are not looping and at the end of the AVI
		  m_bRunning=false;
		}
	}
    // Get Sound of frame
	GetFrameSound();
	// Read the next frame
	ReadFrame(m_lIndex-m_asiSound.dwInitialFrames);
	// Count up frame
	m_lIndex++;
}

BOOL CAviSurfaceWithSound::CreateSoundStuff()
{
   DSBUFFERDESC dsbd;
   // At first get the Directsound object
   if (DirectSoundCreate(NULL,&m_lpDS,NULL)!=DS_OK)
   {
	   //Direct Sound creation failed
	   return false;
   }

   // now set the cooperative level - we want to set the outputformat
   // so DSSCL_EXCLUSIVE is needed
   if (m_lpDS->SetCooperativeLevel(m_AviWnd,DSSCL_NORMAL)!=DS_OK)
   {
	   //Unable to set Cooperative Level
	   return false;
   }

   // Create a DSB Description to get the primary soundbuffer
   ZeroMemory(&dsbd,sizeof(dsbd));
   dsbd.dwSize = sizeof(dsbd);
   dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;

   // get the primary Soundbuffer
   if (m_lpDS->CreateSoundBuffer(&dsbd,&m_lpdsPrimary,NULL)!=DS_OK)
   {
		//Unable to obtain primary soundbuffer
	   return false;
   }

   return true;
}

BOOL CAviSurfaceWithSound::DestroySoundStuff()
{
	if(m_lpdsPrimary)
	{
		// Release the primary Soundbuffer
		m_lpdsPrimary->Release();
		m_lpdsPrimary =0;
    }
    if(m_lpDS)
	{
		// Release the DirectSound object
		m_lpDS->Release();
		m_lpDS = 0;
	}

	return true;
}

//bool CAviSurfaceWithSound::InitSound(LPDIRECTSOUND lpDS)
bool CAviSurfaceWithSound::InitSound(void)
{
	LONG lFmtLenght;
	DSBUFFERDESC dsbd;

	// Read the Sound-description from the AVI
	AVIStreamFormatSize(m_pasSound,0,&lFmtLenght);
	// Allocate memory for the soundformat
	m_lpSoundScrFmt = (WAVEFORMATEX *)malloc(lFmtLenght);
	// read soundformat
	AVIStreamReadFormat(m_pasSound,0,m_lpSoundScrFmt,&lFmtLenght);
    // get further info of soundstream
	AVIStreamInfo(m_pasSound,&m_asiSound,sizeof(AVISTREAMINFO));


	ZeroMemory(&dsbd,sizeof(dsbd));
	// Create the DSB description
	dsbd.dwSize = sizeof(dsbd);

	// Select a buffersize that we dont have to worry about splitting the loadbuffer
	// when filling the soundbuffer
    dsbd.dwBufferBytes = m_asiSound.dwSuggestedBufferSize * m_dwFps * 2;
    dsbd.lpwfxFormat = m_lpSoundScrFmt;
	m_lpdsbTon = 0;

	// if we have a pointer to the primary soundbuffer
	// adjust outputformat to AVI-Soundstream format
	if (m_lpdsPrimary) {
		m_lpdsPrimary->SetFormat(m_lpSoundScrFmt);
	}

	// Create the DSB
	if (m_lpDS->CreateSoundBuffer(&dsbd,&m_lpdsbTon,NULL)!=DS_OK) {
		CloseSound();
		return false;
	}
    // Initialize Loadpos to DSB
	m_dwLoadPos = 0;
	// Success!
	return true;
}

void CAviSurfaceWithSound::CloseSound()
{
    if (m_lpSoundScrFmt) free(m_lpSoundScrFmt); // free the formatbuffer
	if (m_lpdsbTon)                             // Release the DSB
	   m_lpdsbTon->Release();
}

bool CAviSurfaceWithSound::Start()
{

    // adjust the count of frames
	m_lFrames+=m_asiSound.dwInitialFrames;
	// Read Sound skew
	while (m_lIndex<m_asiSound.dwInitialFrames) {
		GetFrameSound();
		m_lIndex++;
	}
    // start the video playback
	if (!CAviSurface::Start())
		return false;
    GetFrameSound();
	// start the Soundplaying
	return (m_lpdsbTon->Play(0,0,DSBPLAY_LOOPING)==DS_OK);
}

void CAviSurfaceWithSound::Stop()
{
	CAviSurface::Stop(); // Stop Video playback
	m_lpdsbTon->Stop();      // Stop sound playback
}

