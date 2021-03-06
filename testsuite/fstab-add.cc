
#include <stdlib.h>
#include <iostream>

#include <storage/EtcFstab.h>

#include "common.h"


using namespace std;
using namespace storage;


void
test1()
{
    cout << "test1" << endl;

    setup_system("empty");

    EtcFstab fstab("tmp/etc");

    FstabChange entry;
    entry.device = entry.dentry = "/dev/sdb1";
    entry.mount = "/test1";
    entry.fs = "ext4";
    entry.opts = { ("defaults") };

    fstab.addEntry(entry);
    fstab.flush();

    print_fstab();

    cout << endl;
}


void
test2()
{
    cout << "test2" << endl;

    setup_system("empty");

    EtcFstab fstab("tmp/etc");

    FstabChange entry;
    entry.device = entry.dentry = "/dev/sdb1";
    entry.mount = "swap";
    entry.fs = "swap";
    entry.opts = { ("defaults") };

    fstab.addEntry(entry);
    fstab.flush();

    print_fstab();

    cout << endl;
}


void
test3()
{
    cout << "test3" << endl;

    setup_system("empty");

    EtcFstab fstab("tmp/etc");

    FstabChange entry;
    entry.device = "/dev/sdb1";
    entry.dentry = "/dev/mapper/cr_sdb1";
    entry.mount = "/test1";
    entry.fs = "ext4";
    entry.opts = { ("defaults") };
    entry.encr = storage::ENC_LUKS;

    fstab.addEntry(entry);
    fstab.flush();

    print_fstab();
    print_crypttab();

    cout << endl;
}


void
test4()
{
    cout << "test4" << endl;

    setup_system("empty");

    EtcFstab fstab("tmp/etc");

    FstabChange entry;
    entry.device = "/dev/sdb1";
    entry.dentry = "/dev/mapper/cr_sdb1";
    entry.mount = "/test1";
    entry.fs = "ext4";
    entry.opts = { ("defaults") };
    entry.encr = storage::ENC_LUKS;
    entry.tmpcrypt = true;

    fstab.addEntry(entry);
    fstab.flush();

    print_fstab();
    print_crypttab();

    cout << endl;
}


void
test5()
{
    cout << "test5" << endl;

    setup_system("empty");

    EtcFstab fstab("tmp/etc");

    FstabChange entry;
    entry.device = "/dev/sdb1";
    entry.dentry = "UUID=1234";
    entry.mount = "/test1";
    entry.fs = "ext4";
    entry.opts = { ("defaults") };

    fstab.addEntry(entry);
    fstab.flush();

    print_fstab();

    cout << endl;
}


void
test6()
{
    cout << "test6" << endl;

    setup_system("empty");

    EtcFstab fstab("tmp/etc");

    FstabChange entry1;
    entry1.device = "/dev/sda1";
    entry1.dentry = "UUID=1234";
    entry1.mount = "swap";
    entry1.fs = "swap";
    entry1.opts = { ("defaults") };

    FstabChange entry2;
    entry2.device = "/dev/sdb1";
    entry2.dentry = "UUID=5678";
    entry2.mount = "swap";
    entry2.fs = "swap";
    entry2.opts = { ("defaults") };

    fstab.addEntry(entry1);
    fstab.addEntry(entry2);
    fstab.flush();

    print_fstab();

    cout << endl;
}


int
main()
{
    setup_logger();

    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}
