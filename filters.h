//  filters.h
//  
//  Created by Steve Kent on 5/23/17.
//
//  Last update on 5/27/17
#include "source.h"
#include "sink.h"

class filter:public source, public sink
{
	public:
		virtual void Update();
		virtual const char* sinkName();
		virtual const char* sourceName();
		virtual const char* filterName() = 0;
};

class Color:public source
{
	public:
		
		const char* sourceName();
		int width, height;
		unsigned char red, green, blue;
		Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
		{width = w; height = h; red =r; green = g; blue = b;};
		void Execute();
		virtual void Update();

};

class CheckSum:public sink
{
	public:
		unsigned char redCount, greenCount, blueCount;
		const char* sinkName();
		void OutputCheckSum(const char *filename);
		void Execute();
		virtual void Update();
};

class Shrinker:public filter
{
	public:
		const char* filterName();
		void Execute();
};

class LRConcat:public filter
{
	public:
		const char* filterName();
		void Execute();
};

class TBConcat:public filter
{
	public:
		const char* filterName();
		void Execute();
};

class Blender:public filter
{
	private:
		float factor;
	public:
		const char* filterName();
		void Execute();
		void SetFactor(float fctr);
};

class Mirror:public filter
{
	public:
		const char* filterName();
		void Execute();
};

class Rotate:public filter
{
	public:
		const char* filterName();
		void Execute();
};

class Subtract:public filter
{
	public:
		const char* filterName();
		void Execute();
};

class Grayscale:public filter
{
	public:
		const char* filterName();
		void Execute();
};

class Blur:public filter
{
	public:
		const char* filterName();
		void Execute();
};