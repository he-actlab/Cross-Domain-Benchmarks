 
#include <math.h>

 #include <libavutil/opt.h>
 #include <libavcodec/avcodec.h>
 #include <libavutil/channel_layout.h>
 #include <libavutil/common.h>
 #include <libavutil/imgutils.h>
 #include <libavutil/mathematics.h>
 #include <libavutil/samplefmt.h>
 
 #define INBUF_SIZE 4096
 #define AUDIO_INBUF_SIZE 20480
 #define AUDIO_REFILL_THRESH 4096


 /*
  * Video decoding example
  */
 static void pgm_save(unsigned char *buf, int wrap, int xsize, int ysize,
                      char *filename)
 {
     FILE *f;
     int i;
 
     f = fopen(filename,"w");
     fprintf(f, "P5\n%d %d\n%d\n", xsize, ysize, 255);
     for (i = 0; i < ysize; i++)
         fwrite(buf + i * wrap, 1, xsize, f);
     fclose(f);
 }
 
 static int decode_write_frame(const char *outfilename, AVCodecContext *avctx,
                               AVFrame *frame, int *frame_count, AVPacket *pkt, int last)
 {
     int len, got_frame;
     char buf[1024];
 
     len = avcodec_decode_video2(avctx, frame, &got_frame, pkt);
     if (len < 0) {
         fprintf(stderr, "Error while decoding frame %d\n", *frame_count);
         return len;
     }
     if (got_frame) {
         printf("Saving %sframe %3d\n", last ? "last " : "", *frame_count);
         fflush(stdout);
 
         /* the picture is allocated by the decoder, no need to free it */
         snprintf(buf, sizeof(buf), outfilename, *frame_count);
         pgm_save(frame->data[0], frame->linesize[0],
                  frame->width, frame->height, buf);
         (*frame_count)++;
     }
     if (pkt->data) {
         pkt->size -= len;
         pkt->data += len;
     }
     return 0;
 }
 
 static void video_decode_example(const char *outfilename, const char *filename)
 {
     AVCodec *codec;
     AVCodecContext *c= NULL;
     int frame_count;
     FILE *f;
     AVFrame *frame;
     uint8_t inbuf[INBUF_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
     AVPacket avpkt;
 
     av_init_packet(&avpkt);
 
     /* set end of buffer to 0 (this ensures that no overreading happens for damaged MPEG streams) */
     memset(inbuf + INBUF_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);
 
     printf("Decode video file %s to %s\n", filename, outfilename);
 
     /* find the MPEG-1 video decoder */
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
 
     /* For some codecs, such as msmpeg4 and mpeg4, width and height
        MUST be initialized there because this information is not
        available in the bitstream. */
 
     /* open it */
     if (avcodec_open2(c, codec, NULL) < 0) {
         fprintf(stderr, "Could not open codec\n");
         exit(1);
     }
 
     f = fopen(filename, "rb");
     if (!f) {
         fprintf(stderr, "Could not open %s\n", filename);
         exit(1);
     }
 
     frame = av_frame_alloc();
     if (!frame) {
         fprintf(stderr, "Could not allocate video frame\n");
         exit(1);
     }
 
     frame_count = 0;
     for (;;) {
         avpkt.size = fread(inbuf, 1, INBUF_SIZE, f);
         if (avpkt.size == 0)
             break;
 
         /* NOTE1: some codecs are stream based (mpegvideo, mpegaudio)
            and this is the only method to use them because you cannot
            know the compressed data size before analysing it.
 
            BUT some other codecs (msmpeg4, mpeg4) are inherently frame
            based, so you must call them with all the data for one
            frame exactly. You must also initialize 'width' and
            'height' before initializing them. */
 
         /* NOTE2: some codecs allow the raw parameters (frame size,
            sample rate) to be changed at any frame. We handle this, so
            you should also take care of it */
 
         /* here, we use a stream based decoder (mpeg1video), so we
            feed decoder and see if it could decode a frame */
         avpkt.data = inbuf;
         while (avpkt.size > 0)
             if (decode_write_frame(outfilename, c, frame, &frame_count, &avpkt, 0) < 0)
                 exit(1);
     }
 
     /* Some codecs, such as MPEG, transmit the I- and P-frame with a
        latency of one frame. You must do the following to have a
        chance to get the last frame of the video. */
     avpkt.data = NULL;
     avpkt.size = 0;
     decode_write_frame(outfilename, c, frame, &frame_count, &avpkt, 1);
 
     fclose(f);
 
     avcodec_free_context(&c);
     av_frame_free(&frame);
 //    printf("\n");
 }


int mpeg_decode()
 {
     /* register all the codecs */
     avcodec_register_all();
 
	 //video_encode_example("test.mpg", AV_CODEC_ID_MPEG1VIDEO);
     video_decode_example("test%02d.pgm", "data/test.mpg");
    
     return 0;
 }

