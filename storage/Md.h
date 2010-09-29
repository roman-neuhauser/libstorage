/*
 * Copyright (c) [2004-2010] Novell, Inc.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#ifndef MD_H
#define MD_H

#include "storage/StorageInterface.h"
#include "storage/Volume.h"

namespace storage
{
    class MdCo;
    class EtcMdadm;


class Md : public Volume
    {
	friend class ProcMdstat;
	friend class MdPartCo;

    public:
	Md(const MdCo& c, unsigned Pnr, MdType Type, const list<string>& devs, const list<string>& spares);
	Md(const MdCo& c, const string& line, SystemInfo& systeminfo);
	Md(const MdCo& c, const Md& v);
	virtual ~Md();

	storage::MdType personality() const { return md_type; }
	void setPersonality( storage::MdType val ); 
	storage::MdParity parity() const { return md_parity; }
	int setParity( storage::MdParity val ); 
	unsigned long chunkSize() const { return chunk; }
	void setChunkSize( unsigned long val ) { chunk=val; }
	void setMdUuid( const string&val ) { md_uuid=val; }
	bool destroySb() const { return( destrSb ); }
	void setDestroySb( bool val=true ) { destrSb=val; }
	const string& getMdUuid() const { return(md_uuid); }
	const string& pName() const { return md_names[md_type]; }
	const string& ptName() const { return par_names[md_parity]; }
	list<string> getDevs(bool all = true, bool spare = false) const;
	int checkDevices();
	int addDevice( const string& dev, bool spare=false );
	int removeDevice( const string& dev );
	string createCmd() const;
	static bool matchRegex( const string& dev );
	static unsigned mdMajor();

	void updateData(SystemInfo& systeminfo);
	void setUdevData(SystemInfo& systeminfo);

	virtual list<string> udevId() const { return udev_id; }

	virtual string procName() const { return nm; }
	virtual string sysfsPath() const;

	static const string& pName(MdType t) { return md_names[t]; }
	static const string& ptName(MdParity p) { return par_names[p]; }
	static bool mdStringNum( const string& name, unsigned& num ); 
	static string mdDevice( unsigned num );

	friend std::ostream& operator<< (std::ostream& s, const Md& m );
	virtual void print( std::ostream& s ) const { s << *this; }
	Text removeText( bool doing ) const;
	Text createText( bool doing ) const;
	Text formatText( bool doing ) const;
	static bool notDeleted( const Md& l ) { return( !l.deleted() ); }
	void changeDeviceName( const string& old, const string& nw );

	void getInfo( storage::MdInfo& info ) const;
	bool equalContent( const Md& rhs ) const;
	void logDifference( const Md& d ) const;
	void getState(MdStateInfo& info) const;

	bool updateEntry(EtcMdadm* mdadm) const;

    protected:

	void computeSize();

	static MdType toMdType(const string& val);
	static MdParity toMdParity(const string& val);
	static MdArrayState toMdArrayState(const string& val);

	void getParent();
	void setMetadata();

	storage::MdType md_type;
	storage::MdParity md_parity;
	unsigned long chunk;
	string md_uuid;
	string sb_ver;
	bool destrSb;
	std::list<string> devs;
	std::list<string> spare;

	list<string> udev_id;

	string md_name; // line in /dev/md/*

	//in case of IMSM and DDF raids there is 'container'.
	bool   has_container;
	string md_metadata;
	string parent_container;
	string parent_uuid;
	string parent_md_name;
	string parent_metadata;
	string md_member;

	static const string md_names[MULTIPATH + 1];
	static const string par_names[PAR_LAST_ENTRY];
	static const string md_states[ACTIVE_IDLE + 1];

	static unsigned md_major;

	mutable storage::MdInfo info; // workaround for broken ycp bindings

    private:

	Md(const Md&);		      // disallow
	Md& operator=(const Md&);     // disallow

    };

}

#endif
