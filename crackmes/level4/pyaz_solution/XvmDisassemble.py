#!/usr/bin/env python3

import struct


REGS = ['r0', 'r1', 'r2', 'r3', 'r4', 'r5', 'r6', 'r7', 'r8', 'r9', 'r10', 'r11', 'r12', 'pc', 'r14', 'sp']
FMT1 = '{:<8s}{:s}'
FMT2 = '{:<8s}{:s}, {:s}'

def GetOperand(b, offset, mode):
    length = 0
    if mode == 0:
        op = ''
    elif mode == 1:
        op = REGS[b[offset]]
        length += 1
    elif mode == 2:
        op = hex(struct.unpack_from('<I', b, offset)[0])
        length += 4
    else:
        if mode & 3 == 0:
            raise Exception('Illegal instruction')
        op = '['
        if mode & 1 != 0:
            op += REGS[b[offset]]
            length += 1
        if mode & 2 != 0:
            if mode & 1 != 0:
                addr = struct.unpack_from('<i', b, offset+length)[0]
            else:
                addr = struct.unpack_from('<I', b, offset+length)[0]
            if addr != 0:
                if addr > 0: op += '+' + hex(addr)
                else: op += hex(addr)
            length += 4
        op += ']'
    return length, op

def SpecifySize(op, sz):
    if op.startswith('['):
        if sz == 1:
            op = 'byte ' + op
        elif sz == 2:
            op = 'word ' + op
        elif sz == 4:
            op = 'dword ' + op
    elif not op.startswith('0x'):
        if sz == 1:
            op += 'b'
        elif sz == 2:
            op += 'w'
    return op

def DecodeInstruction(b, offset):
    opcode = b[offset]
    mode1  = b[offset+1] & 0xf
    mode2  = b[offset+1] >> 4

    length = 2
    if mode1 == 0 and mode2 != 0:
        raise Exception('Illegal instruction')

    l1, op1 = GetOperand(b, offset+length, mode1)
    length += l1
    l2, op2 = GetOperand(b, offset+length, mode2)
    length += l2

    if opcode == 0:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('mov', op1, op2)
    elif opcode == 1:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('mov', op1, op2)
    elif opcode == 2:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('mov', op1, op2)
    elif opcode == 3:
        res = 'nop'
        length = 2
    elif opcode == 4:
        res = 'hlt'
        length = 2
    elif opcode == 5:
        res = 'ret'
    elif opcode == 6:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('call', op1)
    elif opcode == 7:
        res = 'syscall'
    elif opcode == 8:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('shl', op1, op2)
    elif opcode == 9:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('shr', op1, op2)
    elif opcode == 10:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('add', op1, op2)
    elif opcode == 11:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('add', op1, op2)
    elif opcode == 12:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('add', op1, op2)
    elif opcode == 13:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('sub', op1, op2)
    elif opcode == 14:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('sub', op1, op2)
    elif opcode == 15:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('sub', op1, op2)
    elif opcode == 16:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('mul', op1, op2)
    elif opcode == 17:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('mul', op1, op2)
    elif opcode == 18:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('mul', op1, op2)
    elif opcode == 19:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('div', op1, op2)
    elif opcode == 20:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('div', op1, op2)
    elif opcode == 21:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('div', op1, op2)
    elif opcode == 22:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('xor', op1, op2)
    elif opcode == 23:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('xor', op1, op2)
    elif opcode == 24:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('xor', op1, op2)
    elif opcode == 25:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('and', op1, op2)
    elif opcode == 26:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('and', op1, op2)
    elif opcode == 27:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('and', op1, op2)
    elif opcode == 28:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('or', op1, op2)
    elif opcode == 29:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('or', op1, op2)
    elif opcode == 30:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('or', op1, op2)
    elif opcode == 31:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('not', op1)
    elif opcode == 32:
        op1 = SpecifySize(op1, 1)
        res = FMT1.format('not', op1)
    elif opcode == 33:
        op1 = SpecifySize(op1, 2)
        res = FMT1.format('not', op1)
    elif opcode == 34:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('push', op1)
    elif opcode == 35:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('pop', op1)
    elif opcode == 36:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('xchg', op1, op2)
    elif opcode == 37:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('inc', op1)
    elif opcode == 38:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('dec', op1)
    elif opcode == 39:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('cmp', op1, op2)
    elif opcode == 40:
        op1 = SpecifySize(op1, 1)
        op2 = SpecifySize(op2, 1)
        res = FMT2.format('cmp', op1, op2)
    elif opcode == 41:
        op1 = SpecifySize(op1, 2)
        op2 = SpecifySize(op2, 2)
        res = FMT2.format('cmp', op1, op2)
    elif opcode == 42:
        op1 = SpecifySize(op1, 4)
        op2 = SpecifySize(op2, 4)
        res = FMT2.format('test', op1, op2)
    elif opcode == 43:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('jmp', op1)
    elif opcode == 44:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('je', op1)
    elif opcode == 45:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('jne', op1)
    elif opcode == 46:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('ja', op1)
    elif opcode == 47:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('jb', op1)
    elif opcode == 48:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('jae', op1)
    elif opcode == 49:
        op1 = SpecifySize(op1, 4)
        res = FMT1.format('jbe', op1)
    else:
        res = 'nop'
        length = 2
    return length, res

def Analyze(prog, additional=None):
    lines = dict()
    queue = [prog.Entry]
    if additional is not None:
        queue += list(additional)
    b = prog.Binary
    while queue:
        addr = queue.pop()
        if addr in lines:
            continue
        offset = prog.AddressToOffset(addr)
        while True:
            l, s = DecodeInstruction(b, offset)
            lines[addr] = s
            if s == 'hlt' or s == 'ret':
                break
            if s.startswith('j') or s.startswith('call'):
                target = s.split()[1]
                if target.startswith('0x'):
                    queue.append(int(target, 16))
                if s.startswith('jmp'):
                    break
            addr += l
            offset += l
            if addr in lines:
                break
    return lines




