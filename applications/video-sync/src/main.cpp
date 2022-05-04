#include <math.h>

extern "C" { 
 #include <libavutil/opt.h>
 #include <libavcodec/avcodec.h>
 #include <libavutil/channel_layout.h>
 #include <libavutil/common.h>
 #include <libavutil/imgutils.h>
 #include <libavutil/mathematics.h>
 #include <libavutil/samplefmt.h>
} 
 #define INBUF_SIZE 4096
 #define AUDIO_INBUF_SIZE 20480
 #define AUDIO_REFILL_THRESH 4096

#include <cstdio>
#include <iostream>
#include "fourier.hpp"
#include <fstream>
#include <time.h>

static int* indices;
static Complex* x;
static Complex* f;

#define FRAME_COUNT 25


static int decode_write_frame(const char *outfilename, AVCodecContext *avctx,
                               AVFrame *frame, int *frame_count, AVPacket *pkt, int last) {
     int len, got_frame;
     char buf[1024];
 
     len = avcodec_decode_video2(avctx, frame, &got_frame, pkt);
     if (len < 0) {
         fprintf(stderr, "Error while decoding frame %d\n", *frame_count);
         return len;
     }
     if (got_frame) {
         fflush(stdout);
         snprintf(buf, sizeof(buf), outfilename, *frame_count);
         (*frame_count)++;
     }
     if (pkt->data) {
         pkt->size -= len;
         pkt->data += len;
     }
     return 0;
 }
 
 static void video_decode_example(const char *outfilename, const char *filename,
AVFrame **decoded_frame)
 {
     AVCodec *codec;
     AVCodecContext *c= NULL;
     int frame_count;
     FILE *f;
     AVFrame *frame;
     uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
     AVPacket avpkt;
 
     av_init_packet(&avpkt);
     memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);
 
     codec = avcodec_find_decoder(AV_CODEC_ID_MPEG1VIDEO);
     if (!codec) {
         fprintf(stderr, "Codec not found\n");
         exit(1);
     }
 
     c = avcodec_alloc_context3(codec);
     if (!c) {
         fprintf(stderr, "Could not allocate video codec context\n");
         exit(1);
     }
 
     if (codec->capabilities & AV_CODEC_CAP_TRUNCATED)
         c->flags |= AV_CODEC_FLAG_TRUNCATED; // we do not send complete frames
 
     if (avcodec_open2(c, codec, NULL) < 0) {
         fprintf(stderr, "Could not open codec\n");
         exit(1);
     }
 
     f = fopen(filename, "rb");
     if (!f) {
         fprintf(stderr, "Could not open %s\n", filename);
         exit(1);
     }

	 frame_count = 0;
     for (;;) {
         avpkt.size = fread(inbuf, 1, INBUF_SIZE, f);
         if (avpkt.size == 0)
             break;
 
         avpkt.data = inbuf;
         while (avpkt.size > 0) {
			 frame = av_frame_alloc();
			 if (!frame) {
				 fprintf(stderr, "Could not allocate video frame\n");
				 exit(1);
			 }
             if (decode_write_frame(outfilename, c, frame, &frame_count, &avpkt, 0) < 0)
                 exit(1);
			*decoded_frame++ = frame;	
		}
     }
 
     avpkt.data = NULL;
     avpkt.size = 0;
     decode_write_frame(outfilename, c, frame, &frame_count, &avpkt, 1);

     fclose(f);
 
     avcodec_free_context(&c);
     av_frame_free(&frame);
 }


int main(int argc, char **argv)
 {
    avcodec_register_all();
	AVFrame *decoded_frame[FRAME_COUNT];
    video_decode_example("test%02d.pgm", "data/test.mpg", decoded_frame);
	int n = 32768;
	std::string outputFilename 	= "data/fft_out.data";

	std::ofstream outputFileHandler;
	outputFileHandler.open(outputFilename);
	outputFileHandler.precision(5);

	x 		= (Complex*)malloc(n * sizeof (Complex));
	f 		= (Complex*)malloc(n * sizeof (Complex));
	indices = (int*)malloc(n * sizeof (int));

	if(x == NULL || f == NULL || indices == NULL)
	{
		std::cout << "cannot allocate memory for the triangle coordinates!" << std::endl;
		return -1 ;
	}

	int K = n;

	for (int i = 0;i < K ; i++)
	{
		x[i].real = i;
		x[i].imag = 0 ;
	}
	radix2DitCooleyTykeyFft(K, indices, x, f) ;
	
	for (int i = 0;i < K ; i++)
	{
		outputFileHandler << f[i].real << " " << f[i].imag << std::endl;
	}

	outputFileHandler.close();
     
     return 0;
}
