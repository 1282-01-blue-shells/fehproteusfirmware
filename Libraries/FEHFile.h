#ifndef FEHFILE_H
#define FEHFILE_H

class FEHFile
{
	public:
		FIL wrapper;
		static int prevFileId;
		int fileIdNum;
		FEHFile() {
			fileIdNum = ++prevFileId;
		}
}; 
#endif
