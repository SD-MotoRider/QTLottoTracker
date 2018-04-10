#ifndef POWERBALLREADER_H
#define POWERBALLREADER_H

#include "DrawReader.h"

class PowerballReader :
	public DrawReader
{
public:
	PowerballReader();
	virtual ~PowerballReader();

	virtual QString name(void);
	virtual SourceType sourceType(void);
	virtual bool open(void);
	virtual bool getNextDraw(Draw& draw);
	virtual void close(void);
};

#endif // DRAWREADER_H
