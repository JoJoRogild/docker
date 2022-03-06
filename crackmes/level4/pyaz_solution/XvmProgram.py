#!/usr/bin/env python3

import struct
import dataclasses


@dataclasses.dataclass
class Section:
    Name        : str
    VAddr       : int
    VSize       : int
    RAddr       : int
    RSize       : int
    Protect     : int
    
    info_fmt = "{:12s} 0x{:<8x}    0x{:<8x} 0x{:<8x} 0x{:<8x} {:s}"
    info_hdr = "{:12s} {:10s}    {:10s} {:10s} {:10s} {:s}".format("Name", "VAddr", "VSize", "RAddr", "RSize", "Protect")
    
    def __str__(self):
        prot = ''
        if self.Protect & 1: prot += 'R'
        if self.Protect & 2: prot += 'W'
        if self.Protect & 4: prot += 'X'
        return Section.info_fmt.format(self.Name, self.VAddr, self.VSize, self.RAddr, self.RSize, prot)


@dataclasses.dataclass
class Symbol:
    Name        : str
    Address     : int


class XvmProgram:

    def __init__(self, filename):
        with open(filename, 'rb') as f:
            self.Binary = bytearray(f.read())
        self._ParseBinary()

    def fromBytes(binary):
        xvm = XvmProgram.__new__(XvmProgram)
        xvm.Binary = bytearray(binary)
        xvm._ParseBinary()
        return xvm

    def _ParseBinary(self):
        magic, entry, nsyms, a, nsecs = struct.unpack_from('<IIIII', self.Binary, 0)
        if magic != 0x36d7678:
            raise Exception('Missing XVM file signature')
        self.Entry = entry
        
        # Load sections
        self.Sections = [None] * nsecs
        sectbl = 0x14 + 8*nsyms
        for i in range(nsecs):
            if struct.unpack_from('<I', self.Binary, sectbl)[0] != 0xdeadbeef:
                raise Exception('Missing XVM section header')
            name = ExtractString(self.Binary, sectbl+4)
            vsz, va, prot, rsz = struct.unpack_from('<IIII', self.Binary, sectbl+5+len(name))
            vsz = min(vsz, 0x10000)
            rsz = min(vsz, rsz)
            self.Sections[i] = Section(Name=name, VAddr=va, VSize=vsz, RAddr=sectbl+21+len(name), RSize=rsz, Protect=prot)
            sectbl += 21+len(name)+rsz

        # Load symbols
        self.Symbols = [None] * nsyms
        symtbl = 0x14
        for i in range(nsyms):
            name, addr = struct.unpack_from('<II', self.Binary, symtbl+8*i)
            name = ExtractString(self.Binary, self.AddressToOffset(name))
            self.Symbols[i] = Symbol(Name=name, Address=addr)

    def AddressToOffset(self, addr):
        for s in self.Sections:
            if s.VAddr <= addr and addr < s.VAddr + s.VSize:
                return s.RAddr + addr - s.VAddr

    def PrintSummary(self):
        print(f'Sections: {len(self.Sections)}')
        print(f'Symbols:  {len(self.Symbols)}')
        print(f'Entry:    0x{self.Entry:x}')

    def PrintSections(self):
        print(Section.info_hdr)
        for s in self.Sections:
            print(s)

    def PrintSymbols(self):
        for s in self.Symbols:
            print(f'0x{s.Address:<8x} {s.Name:s}')




def ExtractString(b, off):
    ind = b.find(b'\x00', off)
    if ind >= 0:
        return b[off:ind].decode('utf-8')
    else:
        return b[off:].decode('utf-8')
