//True and false are equal to 1 and 0, respectively.
#define true 1
#define True 1
#define false 0
#define False 0

/*
    1. The number of files, N, is a 4-byte unsigned integer.
    2. The size of each file name 1-byte is a unsigned char.
    3. The size of each file is a 4-byte unsigned integer.
    4. The length of each filename is 1 <= li <= 255, therefore a constant for 255.
*/

#define SIZEnumOfFilesInArchive 4 //1
#define SIZElengthOfFileName 1 //3
#define SIZElengthOfFile 4 //2
#define	SIZEmaxFileName 255 //4
