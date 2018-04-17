/*
 * read_ samples程序处理从一个以地址in起始的N个16位的音频采样数据。
 * 这个音频采样数据是'小端'的(例如从a.wav文件),而且不知是否字节对齐的。
 * 程序把采样数据复制到以out指向的short类型的数组。这些采样数据
 * 将会根据ARM内存的字节排序方式来存储。该程序高效处理了所有可能
 * 的地址边界问题和ARM字节排序方式的配置。
 *
 */

void read_sample(short *out,char *in,unsigned int N)
{
    unsigned short *data;
    unsigned int sample,next;

    switch((unsigned int)in&1){         //根据地址:0位是否为1来判断边界对齐情况
        case 0:
            data = (unsigned short *)in;
            do
            {
                sample = *(data++);
#ifdef __BIG_ENDIAN                 
                sample=((sample>>8)|(sample)<<8);//当处理器是大端模式，而输入数据是小端模式时
#endif
                *(out++) = (short)sample;//when all are little endian
            }while(--N);
            break;

        case 1:
            data = (unsigned short *)(in-1);
            sample = *(data++);
            //to get the first byte
#ifdef __BIG_ENDIAN
            sample&=0xff;
#else
            sample>>=8;
#endif
            do
            {
                next=*(data++);
                //get the second byte and combiled with the first byte
#ifdef __BIG_ENDIAN
                *(out++)=(short)((next&0xff00)|sample);
                sample = next&0xff;
#else
                *(out++)=(short)((next<<8)|sample);
                sample = next>>8;
#endif
            }while(--N)
            break;
    }
}
