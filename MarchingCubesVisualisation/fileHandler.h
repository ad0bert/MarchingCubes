#ifndef _FILE_HANDLER_H
#define _FILE_HANDLER_H

#include <string>
#include <vector>

#include "dbh.h"

#define swap_short(num) ((num>>8) | (num<<8));
#define swap_long(num) (((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000)) 

typedef enum fileType{img, hdr};
typedef std::vector<std::vector<std::vector<float>>> d3Buffer;

class fileHandler{
public:
    fileHandler();
    void setPath(std::string path);
    void setType(fileType type);
	void setHdr(struct dsr hdr);
	struct dsr getHdr();
	bool readFile();
	bool createStl();
	d3Buffer getData();
private:
	bool readImg(FILE *fp);
	void readHdr(FILE *fp);

	void swapHdr();
	void showHdr();

	std::string mPath;
	fileType mType;
	struct dsr mHdr;
	d3Buffer mData;
};

#endif // _FILE_HANDLER_H
