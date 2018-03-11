
void storeInfo(flight flightInfo, FILE * outputFile){
	 fseek(outputFile,0, SEEK_END);// checks file, and seeks all the way to the end
	 fwrite(&flightInfo, 1, );

}