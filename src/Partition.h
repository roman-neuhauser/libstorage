#ifndef PARTITION_H
#define PARTITION_H

using namespace std;

#include "y2storage/StorageInterface.h"
#include "y2storage/Volume.h"
#include "y2storage/Region.h"

using namespace storage;


class Disk;

class Partition : public Volume
    {
    public:

	typedef enum { ID_DOS16=0x6, ID_DOS=0x0c, ID_NTFS=0x07, 
	               ID_EXTENDED=0x0f,
		       ID_LINUX=0x83, ID_SWAP=0x82, ID_LVM=0x8e, ID_RAID=0xfd, 
		       ID_APPLE_OTHER=0x101, ID_APPLE_HFS=0x102,
		       ID_GPT_BOOT=0x103, ID_GPT_SERVICE=0x104 } IdNum;

	Partition( const Disk& d, unsigned Pnr, unsigned long long SizeK,
	           unsigned long Start, unsigned long CSize,
		   PartitionType Type, const string& parted_start,
		   unsigned id=ID_LINUX, bool Boot=false );
	Partition( const Disk& d, const string& Data );
	virtual ~Partition();

	unsigned long cylStart() const { return reg.start(); }
	unsigned long cylSize() const { return reg.len(); }
	bool intersectArea( const Region& r ) const;
	bool boot() const { return bootflag; }
	unsigned id() const { return idt; }
	PartitionType type() const { return typ; }
	ostream& logData( ostream& file ) const;
	const string& partedStart() const { return parted_start; }
	friend ostream& operator<< (ostream& s, const Partition &p );
	static bool notDeleted( const Partition&d ) { return( !d.deleted() ); }

	PartitionInfo getPartitionInfo () const;

    protected:
	Region reg;
	bool bootflag;
	PartitionType typ;
	unsigned idt;
	string parted_start;

    };


inline ostream& operator<< (ostream& s, const Partition &p )
    {
    s << "Partition " << Volume(p)
      << " Start:" << p.reg.start()
      << " CylNum:" << p.reg.len()
      << " Id:" << std::hex << p.idt << std::dec;
    if( p.typ!=PRIMARY )
      s << ((p.typ==LOGICAL)?" logical":" extended");
    if( p.bootflag )
      s << " boot";
    return( s );
    }

#endif
