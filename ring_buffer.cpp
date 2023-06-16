#include <stdio.h>
#include <array>
#define IN
#define OUT 
using uint8 = unsigned char;
static constexpr int RingBufferSize = 32;
class RingBuffer
{
public:
	//전송할 데이터를 버퍼에 쓴다
	bool Push(const uint8* IN pData, size_t nSize)
	{
		if (!pData)
		{
			return false;
		}
		if (nSize <= 0)
		{
			return true;
		}
		size_t writableSize = GetWritableSize();
		if (writableSize < nSize)
		{
			return false;
		}
		int i = 0;
		while (nSize--)
		{
			array_[wpos_++] = pData[i];
			if (wpos_ >= RingBufferSize)
			{
				wpos_ = 0;
			}
		}
		return true;
	}
	//버퍼에 받은 데이터를 nSize 만큼 가져온다
	bool Pop(uint8* OUT pData, size_t nSize) 
	{
		if (!pData)
		{
			return false;
		}
		if (nSize <= 0)
		{
			return true;
		}
		size_t readableSize = GetReadableSize();
		if (readableSize < nSize)
		{
			return false;
		}
		int i = 0;
		while (nSize--)
		{
			pData[i] = array_[rpos_++];
			if (rpos_ >= RingBufferSize)
			{
				rpos_ = 0;
			}
		}
		return true;
	}
	//버퍼에 Push할 수 있는 사이즈 리턴
	size_t GetWritableSize()
	{
		if (wpos_ >= rpos_)
		{
			return (RingBufferSize - wpos_) + rpos_;
		}
		else
		{
			return rpos_ - wpos_;
		}
	}
	size_t GetReadableSize()
	{
		if (wpos_ >= rpos_)
		{
			return wpos_ - rpos_;
		}
		else
		{
			return (RingBufferSize - rpos_) + wpos_;
		}
	}
	size_t RPos()
	{
		return rpos_;
	}
	size_t WPos()
	{
		return wpos_;
	}
private:
	size_t rpos_ = 0;
	size_t wpos_ = 0;
	std::array<uint8, RingBufferSize> array_;
};

int main()
{
	bool ret;
	RingBuffer buf;
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	uint8 sub_buf1[] = "Hello World!";
	ret = buf.Push(sub_buf1, sizeof(sub_buf1));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	ret = buf.Push(sub_buf1, sizeof(sub_buf1));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	ret = buf.Push(sub_buf1, sizeof(sub_buf1));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	uint8 sub_buf2[sizeof(sub_buf1)] = { 0, };
	uint8 sub_buf3[7] = { 0, };
	ret = buf.Pop(sub_buf3, sizeof(sub_buf3));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	uint8 sub_buf4[6] = { 0, };
	ret = buf.Pop(sub_buf4, sizeof(sub_buf4));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	ret = buf.Pop(sub_buf2, sizeof(sub_buf2));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	ret = buf.Push(sub_buf1, sizeof(sub_buf1));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	ret = buf.Pop(sub_buf2, sizeof(sub_buf2));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	ret = buf.Pop(sub_buf2, sizeof(sub_buf2));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	ret = buf.Pop(sub_buf2, sizeof(sub_buf2));
	printf("ret: %d\n", ret);
	printf("readable:%lld, writable:%lld, rpos:%lld, wpos:%lld\n", buf.GetReadableSize(), buf.GetWritableSize(), buf.RPos(), buf.WPos());
	system("pause");
	return 0;
}