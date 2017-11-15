
#ifndef NETWORK_H_PROCESSEDTMP_H_
#define NETWORK_H_PROCESSEDTMP_H_
#include <string>

class Processed_Tmp {
public:
	Processed_Tmp( std::string video_id, std::string data, int instruction, int mat, int order );
	Processed_Tmp( int instr );
	Processed_Tmp();
	void delete_data();
	bool operator < ( const Processed_Tmp& tmp );
	virtual ~Processed_Tmp();
public:
	std::string vid_id;
	std::string _data;
	int _instruction;
	int _mat;
	int _order;
};

#endif /* NETWORK_H_PROCESSEDTMP_H_ */
