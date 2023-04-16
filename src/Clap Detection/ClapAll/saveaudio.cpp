
PortAudio  2.0

    Main Page
    Related Pages
    Modules
    Data Structures
    Files

    File List
    Globals

    examples

paex_record.c
Go to the documentation of this file.
    1 
    6 /*
    7  * $Id$
    8  *
    9  * This program uses the PortAudio Portable Audio Library.
   10  * For more information see: http://www.portaudio.com
   11  * Copyright (c) 1999-2000 Ross Bencina and Phil Burk
   12  *
   13  * Permission is hereby granted, free of charge, to any person obtaining
   14  * a copy of this software and associated documentation files
   15  * (the "Software"), to deal in the Software without restriction,
   16  * including without limitation the rights to use, copy, modify, merge,
   17  * publish, distribute, sublicense, and/or sell copies of the Software,
   18  * and to permit persons to whom the Software is furnished to do so,
   19  * subject to the following conditions:
   20  *
   21  * The above copyright notice and this permission notice shall be
   22  * included in all copies or substantial portions of the Software.
   23  *
   24  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   25  * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   26  * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   27  * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR
   28  * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
   29  * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   30  * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   31  */
   32 
   33 /*
   34  * The text above constitutes the entire PortAudio license; however, 
   35  * the PortAudio community also makes the following non-binding requests:
   36  *
   37  * Any person wishing to distribute modifications to the Software is
   38  * requested to send the modifications to the original developer so that
   39  * they can be incorporated into the canonical version. It is also 
   40  * requested that these non-binding requests be included along with the 
   41  * license above.
   42  */
   43 
   44 #include <stdio.h>
   45 #include <stdlib.h>
   46 #include "portaudio.h"
   47 
   48 /* #define SAMPLE_RATE  (17932) // Test failure to open with this value. */
   49 #define SAMPLE_RATE  (44100)
   50 #define FRAMES_PER_BUFFER (512)
   51 #define NUM_SECONDS     (5)
   52 #define NUM_CHANNELS    (2)
   53 /* #define DITHER_FLAG     (paDitherOff) */
   54 #define DITHER_FLAG     (0) 
   55 
   56 #define WRITE_TO_FILE   (0)
   57 
   58 /* Select sample format. */
   59 #if 1
   60 #define PA_SAMPLE_TYPE  paFloat32
   61 typedef float SAMPLE;
   62 #define SAMPLE_SILENCE  (0.0f)
   63 #define PRINTF_S_FORMAT "%.8f"
   64 #elif 1
   65 #define PA_SAMPLE_TYPE  paInt16
   66 typedef short SAMPLE;
   67 #define SAMPLE_SILENCE  (0)
   68 #define PRINTF_S_FORMAT "%d"
   69 #elif 0
   70 #define PA_SAMPLE_TYPE  paInt8
   71 typedef char SAMPLE;
   72 #define SAMPLE_SILENCE  (0)
   73 #define PRINTF_S_FORMAT "%d"
   74 #else
   75 #define PA_SAMPLE_TYPE  paUInt8
   76 typedef unsigned char SAMPLE;
   77 #define SAMPLE_SILENCE  (128)
   78 #define PRINTF_S_FORMAT "%d"
   79 #endif
   80 
   81 typedef struct
   82 {
   83     int          frameIndex;  /* Index into sample array. */
   84     int          maxFrameIndex;
   85     SAMPLE      *recordedSamples;
   86 }
   87 paTestData;
   88 
   89 /* This routine will be called by the PortAudio engine when audio is needed.
   90 ** It may be called at interrupt level on some machines so don't do anything
   91 ** that could mess up the system like calling malloc() or free().
   92 */
   93 static int recordCallback( const void *inputBuffer, void *outputBuffer,
   94                            unsigned long framesPerBuffer,
   95                            const PaStreamCallbackTimeInfo* timeInfo,
   96                            PaStreamCallbackFlags statusFlags,
   97                            void *userData )
   98 {
   99     paTestData *data = (paTestData*)userData;
  100     const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
  101     SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
  102     long framesToCalc;
  103     long i;
  104     int finished;
  105     unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;
  106 
  107     (void) outputBuffer; /* Prevent unused variable warnings. */
  108     (void) timeInfo;
  109     (void) statusFlags;
  110     (void) userData;
  111 
  112     if( framesLeft < framesPerBuffer )
  113     {
  114         framesToCalc = framesLeft;
  115         finished = paComplete;
  116     }
  117     else
  118     {
  119         framesToCalc = framesPerBuffer;
  120         finished = paContinue;
  121     }
  122 
  123     if( inputBuffer == NULL )
  124     {
  125         for( i=0; i<framesToCalc; i++ )
  126         {
  127             *wptr++ = SAMPLE_SILENCE;  /* left */
  128             if( NUM_CHANNELS == 2 ) *wptr++ = SAMPLE_SILENCE;  /* right */
  129         }
  130     }
  131     else
  132     {
  133         for( i=0; i<framesToCalc; i++ )
  134         {
  135             *wptr++ = *rptr++;  /* left */
  136             if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
  137         }
  138     }
  139     data->frameIndex += framesToCalc;
  140     return finished;
  141 }
  142 
  143 /* This routine will be called by the PortAudio engine when audio is needed.
  144 ** It may be called at interrupt level on some machines so don't do anything
  145 ** that could mess up the system like calling malloc() or free().
  146 */
  147 static int playCallback( const void *inputBuffer, void *outputBuffer,
  148                          unsigned long framesPerBuffer,
  149                          const PaStreamCallbackTimeInfo* timeInfo,
  150                          PaStreamCallbackFlags statusFlags,
  151                          void *userData )
  152 {
  153     paTestData *data = (paTestData*)userData;
  154     SAMPLE *rptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];
  155     SAMPLE *wptr = (SAMPLE*)outputBuffer;
  156     unsigned int i;
  157     int finished;
  158     unsigned int framesLeft = data->maxFrameIndex - data->frameIndex;
  159 
  160     (void) inputBuffer; /* Prevent unused variable warnings. */
  161     (void) timeInfo;
  162     (void) statusFlags;
  163     (void) userData;
  164 
  165     if( framesLeft < framesPerBuffer )
  166     {
  167         /* final buffer... */
  168         for( i=0; i<framesLeft; i++ )
  169         {
  170             *wptr++ = *rptr++;  /* left */
  171             if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
  172         }
  173         for( ; i<framesPerBuffer; i++ )
  174         {
  175             *wptr++ = 0;  /* left */
  176             if( NUM_CHANNELS == 2 ) *wptr++ = 0;  /* right */
  177         }
  178         data->frameIndex += framesLeft;
  179         finished = paComplete;
  180     }
  181     else
  182     {
  183         for( i=0; i<framesPerBuffer; i++ )
  184         {
  185             *wptr++ = *rptr++;  /* left */
  186             if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
  187         }
  188         data->frameIndex += framesPerBuffer;
  189         finished = paContinue;
  190     }
  191     return finished;
  192 }
  193 
  194 /*******************************************************************/
  195 int main(void);
  196 int main(void)
  197 {
  198     PaStreamParameters  inputParameters,
  199                         outputParameters;
  200     PaStream*           stream;
  201     PaError             err = paNoError;
  202     paTestData          data;
  203     int                 i;
  204     int                 totalFrames;
  205     int                 numSamples;
  206     int                 numBytes;
  207     SAMPLE              max, val;
  208     double              average;
  209 
  210     printf("patest_record.c\n"); fflush(stdout);
  211 
  212     data.maxFrameIndex = totalFrames = NUM_SECONDS * SAMPLE_RATE; /* Record for a few seconds. */
  213     data.frameIndex = 0;
  214     numSamples = totalFrames * NUM_CHANNELS;
  215     numBytes = numSamples * sizeof(SAMPLE);
  216     data.recordedSamples = (SAMPLE *) malloc( numBytes ); /* From now on, recordedSamples is initialised. */
  217     if( data.recordedSamples == NULL )
  218     {
  219         printf("Could not allocate record array.\n");
  220         goto done;
  221     }
  222     for( i=0; i<numSamples; i++ ) data.recordedSamples[i] = 0;
  223 
  224     err = Pa_Initialize();
  225     if( err != paNoError ) goto done;
  226 
  227     inputParameters.device = Pa_GetDefaultInputDevice(); /* default input device */
  228     if (inputParameters.device == paNoDevice) {
  229         fprintf(stderr,"Error: No default input device.\n");
  230         goto done;
  231     }
  232     inputParameters.channelCount = 2;                    /* stereo input */
  233     inputParameters.sampleFormat = PA_SAMPLE_TYPE;
  234     inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
  235     inputParameters.hostApiSpecificStreamInfo = NULL;
  236 
  237     /* Record some audio. -------------------------------------------- */
  238     err = Pa_OpenStream(
  239               &stream,
  240               &inputParameters,
  241               NULL,                  /* &outputParameters, */
  242               SAMPLE_RATE,
  243               FRAMES_PER_BUFFER,
  244               paClipOff,      /* we won't output out of range samples so don't bother clipping them */
  245               recordCallback,
  246               &data );
  247     if( err != paNoError ) goto done;
  248 
  249     err = Pa_StartStream( stream );
  250     if( err != paNoError ) goto done;
  251     printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);
  252 
  253     while( ( err = Pa_IsStreamActive( stream ) ) == 1 )
  254     {
  255         Pa_Sleep(1000);
  256         printf("index = %d\n", data.frameIndex ); fflush(stdout);
  257     }
  258     if( err < 0 ) goto done;
  259 
  260     err = Pa_CloseStream( stream );
  261     if( err != paNoError ) goto done;
  262 
  263     /* Measure maximum peak amplitude. */
  264     max = 0;
  265     average = 0.0;
  266     for( i=0; i<numSamples; i++ )
  267     {
  268         val = data.recordedSamples[i];
  269         if( val < 0 ) val = -val; /* ABS */
  270         if( val > max )
  271         {
  272             max = val;
  273         }
  274         average += val;
  275     }
  276 
  277     average = average / (double)numSamples;
  278 
  279     printf("sample max amplitude = "PRINTF_S_FORMAT"\n", max );
  280     printf("sample average = %lf\n", average );
  281 
  282     /* Write recorded data to a file. */
  283 #if WRITE_TO_FILE
  284     {
  285         FILE  *fid;
  286         fid = fopen("recorded.raw", "wb");
  287         if( fid == NULL )
  288         {
  289             printf("Could not open file.");
  290         }
  291         else
  292         {
  293             fwrite( data.recordedSamples, NUM_CHANNELS * sizeof(SAMPLE), totalFrames, fid );
  294             fclose( fid );
  295             printf("Wrote data to 'recorded.raw'\n");
  296         }
  297     }
  298 #endif
  299 
  300     /* Playback recorded data.  -------------------------------------------- */
  301     data.frameIndex = 0;
  302 
  303     outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
  304     if (outputParameters.device == paNoDevice) {
  305         fprintf(stderr,"Error: No default output device.\n");
  306         goto done;
  307     }
  308     outputParameters.channelCount = 2;                     /* stereo output */
  309     outputParameters.sampleFormat =  PA_SAMPLE_TYPE;
  310     outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
  311     outputParameters.hostApiSpecificStreamInfo = NULL;
  312 
  313     printf("\n=== Now playing back. ===\n"); fflush(stdout);
  314     err = Pa_OpenStream(
  315               &stream,
  316               NULL, /* no input */
  317               &outputParameters,
  318               SAMPLE_RATE,
  319               FRAMES_PER_BUFFER,
  320               paClipOff,      /* we won't output out of range samples so don't bother clipping them */
  321               playCallback,
  322               &data );
  323     if( err != paNoError ) goto done;
  324 
  325     if( stream )
  326     {
  327         err = Pa_StartStream( stream );
  328         if( err != paNoError ) goto done;
  329         
  330         printf("Waiting for playback to finish.\n"); fflush(stdout);
  331 
  332         while( ( err = Pa_IsStreamActive( stream ) ) == 1 ) Pa_Sleep(100);
  333         if( err < 0 ) goto done;
  334         
  335         err = Pa_CloseStream( stream );
  336         if( err != paNoError ) goto done;
  337         
  338         printf("Done.\n"); fflush(stdout);
  339     }
  340 
  341 done:
  342     Pa_Terminate();
  343     if( data.recordedSamples )       /* Sure it is NULL or valid. */
  344         free( data.recordedSamples );
  345     if( err != paNoError )
  346     {
  347         fprintf( stderr, "An error occured while using the portaudio stream\n" );
  348         fprintf( stderr, "Error number: %d\n", err );
  349         fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
  350         err = 1;          /* Always return 0 or 1, but no other return codes. */
  351     }
  352     return err;
  353 }
  354 
Generated by   doxygen 1.8.5
