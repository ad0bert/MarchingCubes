#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include "fileHandler.h"

fileHandler::fileHandler(std::string path, fileType type):mPath(path), mType(type){
	mHdr.dime.dim[0] = -1;
}

void fileHandler::setHdr(struct dsr hdr){
	memcpy(&mHdr, &hdr, 348);
	mData.resize(mHdr.dime.dim[1]);

	for (int i = 0; i < mData.size(); ++i){
		mData[i].resize(mHdr.dime.dim[2]);
		for (int j = 0; j < mData[i].size(); ++j){
			mData[i][j].resize(mHdr.dime.dim[3]);
		}
	}
}

struct dsr fileHandler::getHdr(){
	return mHdr;
}

bool fileHandler::readFile(){
	FILE *fp;
	if ((fp = fopen(mPath.c_str(), "rb+")) == NULL)
	{
		fprintf(stderr, "Can't open:<%s>\n", mPath);
		return false;
	}
	
	bool res = false;

	switch (mType){
	case img:
		res = readImg(fp);
		break;
	case hdr:
		readHdr(fp);
		res = true;
		break;
	default:
		std::cerr << "not supported file type!" << std::endl;
		break;
	}

	fclose(fp);
	return res;
}

void fileHandler::readHdr(FILE *fp){
	fread(&mHdr, 1, sizeof(struct dsr), fp);
	if (mHdr.dime.dim[0] < 0 || mHdr.dime.dim[0] > 15)
		swapHdr();

	showHdr();
}

d3Buffer fileHandler::getData(){
	return mData;
}

bool fileHandler::readImg(FILE *fp){
	int c;
	for (int k = 0; k < mHdr.dime.dim[3]; k++) {
		for (int j = 0; j < mHdr.dime.dim[2]; j++) {
			for (int i = 0; i<mHdr.dime.dim[1]; i++) {
				if ((c = fgetc(fp)) == EOF) {
					fprintf(stderr, "Unexpected end of file\n");
					return false;
				}
				mData[i][j][k] = c;
			}
		}
	}
	return true;
}

void fileHandler::showHdr()
{
	int i;
	char toPrint[128];
	printf("Analyze Header Dump of: <%s> \n", mPath);
	/* Header Key */
	printf("sizeof_hdr: <%d> \n", mHdr.hk.sizeof_hdr);
	printf("data_type: <%s> \n", mHdr.hk.data_type);
	printf("db_name: <%s> \n", mHdr.hk.db_name);
	printf("extents: <%d> \n", mHdr.hk.extents);
	printf("session_error: <%d> \n", mHdr.hk.session_error);
	printf("regular: <%c> \n", mHdr.hk.regular);
	printf("hkey_un0: <%c> \n", mHdr.hk.hkey_un0);
	/* Image Dimension */
	for (i = 0; i<8; i++)
		printf("dim[%d]: <%d> \n", i, mHdr.dime.dim[i]);

	/*strncpy(toPrint, mHdr.dime.vox_units, 4);
	printf("vox_units: <%s> \n", toPrint);*/

	/*strncpy(toPrint, mHdr.dime.pixdim, 8);
	printf("cal_units: <%s> \n", toPrint);*/
	printf("unused1: <%d> \n", mHdr.dime.funused1);
	printf("datatype: <%d> \n", mHdr.dime.datatype);
	printf("bitpix: <%d> \n", mHdr.dime.bitpix);

	for (i = 0; i<8; i++)
		printf("pixdim[%d]: <%6.4f> \n", i, mHdr.dime.pixdim[i]);

	printf("vox_offset: <%6.4> \n", mHdr.dime.vox_offset);
	printf("funused1: <%6.4f> \n", mHdr.dime.funused1);
	printf("funused2: <%6.4f> \n", mHdr.dime.funused2);
	printf("funused3: <%6.4f> \n", mHdr.dime.funused3);
	printf("cal_max: <%6.4f> \n", mHdr.dime.cal_max);
	printf("cal_min: <%6.4f> \n", mHdr.dime.cal_min);
	printf("compressed: <%d> \n", mHdr.dime.compressed);
	printf("verified: <%d> \n", mHdr.dime.verified);
	printf("glmax: <%d> \n", mHdr.dime.glmax);
	printf("glmin: <%d> \n", mHdr.dime.glmin);
	/* Data History */
	strncpy(toPrint, mHdr.hist.descrip, 80);
	printf("descrip: <%s> \n", toPrint);
	strncpy(toPrint, mHdr.hist.aux_file, 24);
	printf("aux_file: <%s> \n", toPrint);
	printf("orient: <%d> \n", mHdr.hist.orient);
	strncpy(toPrint, mHdr.hist.originator, 10);
	printf("originator: <%s> \n", toPrint);
	strncpy(toPrint, mHdr.hist.generated, 10);
	printf("generated: <%s> \n", toPrint);
	strncpy(toPrint, mHdr.hist.scannum, 10);
	printf("scannum: <%s> \n", toPrint);
	strncpy(toPrint, mHdr.hist.patient_id, 10);
	printf("patient_id: <%s> \n", toPrint);
	strncpy(toPrint, mHdr.hist.exp_date, 10);
	printf("exp_date: <%s> \n", toPrint);
	strncpy(toPrint, mHdr.hist.exp_time, 10);
	printf("exp_time: <%s> \n", toPrint);
	strncpy(toPrint, mHdr.hist.hist_un0, 10);
	printf("hist_un0: <%s> \n", toPrint);
	printf("views: <%d> \n", mHdr.hist.views);
	printf("vols_added: <%d> \n", mHdr.hist.vols_added);
	printf("start_field:<%d> \n", mHdr.hist.start_field);
	printf("field_skip: <%d> \n", mHdr.hist.field_skip);
	printf("omax: <%d> \n", mHdr.hist.omax);
	printf("omin: <%d> \n", mHdr.hist.omin);
	printf("smin: <%d> \n", mHdr.hist.smax);
	printf("smin: <%d> \n", mHdr.hist.smin);
}

void fileHandler::swapHdr()
{
	swap_long(mHdr.hk.sizeof_hdr);
	swap_long(mHdr.hk.extents);
	swap_short(mHdr.hk.session_error);
	swap_short(mHdr.dime.dim[0]);
	swap_short(mHdr.dime.dim[1]);
	swap_short(mHdr.dime.dim[2]);
	swap_short(mHdr.dime.dim[3]);
	swap_short(mHdr.dime.dim[4]);
	swap_short(mHdr.dime.dim[5]);
	swap_short(mHdr.dime.dim[6]);
	swap_short(mHdr.dime.dim[7]);
	swap_short((short)mHdr.dime.funused1);
	swap_short(mHdr.dime.datatype);
	swap_short(mHdr.dime.bitpix);
	swap_long((int)mHdr.dime.pixdim[0]);
	swap_long((int)mHdr.dime.pixdim[1]);
	swap_long((int)mHdr.dime.pixdim[2]);
	swap_long((int)mHdr.dime.pixdim[3]);
	swap_long((int)mHdr.dime.pixdim[4]);
	swap_long((int)mHdr.dime.pixdim[5]);
	swap_long((int)mHdr.dime.pixdim[6]);
	swap_long((int)mHdr.dime.pixdim[7]);
	swap_long((int)mHdr.dime.vox_offset);
	swap_long((int)mHdr.dime.funused1);
	swap_long((int)mHdr.dime.funused2);
	swap_long((int)mHdr.dime.cal_max);
	swap_long((int)mHdr.dime.cal_min);
	swap_long((int)mHdr.dime.compressed);
	swap_long((int)mHdr.dime.verified);
	swap_short(mHdr.dime.dim_un0);
	swap_long(mHdr.dime.glmax);
	swap_long(mHdr.dime.glmin);
}