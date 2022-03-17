//d5
ByteRIP += 1

if([ByteRIP - 1] & 3 == 2){
    if(rsi <= rbx){//rbx == rsp
        if(rdi >= rax){
            //some stuff
        }
        else{
            if(r9b|sil == 0 || r8 <= 0x17){
                do while(rdi < rax){

                }
            }
            else{
                do while(r8 != rcx){

                }
            }
        }
    }    
    else{
        if(r10 > rcx || rdi <= 0x17){
            do while(rax < rsi){
                //some stuff
            }
            if(rdi >= rax){
                //some stuff
            }
            else{
                if(r9b|sil == 0 || r8 <= 0x17){
                    do while(rdi < rax){
                        //some stuff
                    }
                    //some stuff
                }
                else{
                    do while(rcx != r8){

                    }
                }
            }
        }
        else{
            do while(rax != rdi){

            }
            if(rdi >= rax){
                //some stuff
            }
            if(r9b|sil == 0 || r8 <= 0x17){
                do while(rdi < rax){
                    //some stuff
                }
                //som stuff
            }
            else{
                do while(rcx != r8){
                    //some stuff
                }
                //some stuff
            }
        }
    }
}
else if([ByteRIP - 1] & 3 == 3){
    eax = shl(((not dword[ByteRIP]) & 7), 2)
    rsi = rbx + rax
    if(rsi <= rbx){//rbx == rsp
        esi = 8 - dword[ByteRIP] & 7
        rax = *var6
        rdi = *[rbx + rsi*4]
        if(rdi >= rax){
            xmm0 = xmmword[rsp]//0x10
            xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
            //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
            //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
            [rsp] = xmm1
            xmm0 = xmm0 switch//den putter det bare op i den anden ende
            //0x0000000000000000000000000a414141
            //0x0a414141000000000000000000000000
            [rsp + 0x10] = xmm0
            //den har byttet stacken om fra før:
            //4141 410a 0000 0000 0000 0000 0000 0000
            //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
            //efter:
            //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
            //0000 0000 0000 0000 0000 0000 4141 410a
            //vær opmærksom på det er ikke tal taget fra lige den her branch
        }
        else{
            r8 = *var6-1-rdi
            rcx = shr(r8, 3)
            r9 = neg(rcx)
            rsi = shl(rsi+rcx+1, 2)
            r9 = r9*4 + 0x1c
            if(r9 >= rsi){
                r9 = 1
            }
            else{
                r9 = 0
            }
            rsi = *ByteRIP
            if(rdi >= rsi){
                sil = 1
            }
            else{
                sil = 0//kun den nederste byte
            }
            or r9b, sil
            if(r9b == 0 || r8 <= 0x17){//så det her er if(r9b == 0 && sil == 0 || r8 <= 0x17)
                do while(rax > rdi){
                    rcx = dword[rdi]//4 bytes
                    esi = dword[rax]//4 bytes
                    rdi += 4
                    rax -= 4
                    [rdi - 4] = esi
                    [rax + 4] = ecx
                    //den her bytter også noget rundt i stacken
                }
                xmm0 = xmmword[rsp]//0x10
                xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
                //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
                //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
                [rsp] = xmm1
                xmm0 = xmm0 switch//den putter det bare op i den anden ende
                //0x0000000000000000000000000a414141
                //0x0a414141000000000000000000000000
                [rsp + 0x10] = xmm0
                //den har byttet stacken om fra før:
                //4141 410a 0000 0000 0000 0000 0000 0000
                //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
                //efter:
                //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
                //0000 0000 0000 0000 0000 0000 4141 410a
            }
            else{
                r9 = rcx + 1
                rsi = rsp + 0x10
                rcx = rdi
                r8 = shl(shr(r9, 2), 4) + rdi
                do while(rcx != r8){
                    xmm0 = xmmword[rcx]//0x10 bytes
                    xmm1 = xmmword[rsi] shift//den bytter endian rundt men kun i grupper af 4 bytes
                    rcx += 0x10
                    [rcx - 0x10] = xmm1
                    rsi -= 0x10
                    xmm0 = xmm0 shift
                    [rsi + 0x10] = xmm0
                }
                rsi = and r9, 0xfffffffffffffffc
                rcx = rdi + rsi*4
                rdi = neg rsi
                rax = rax + rdi*4
                if(r9 !=  rsi){
                    esi = dword[rcx]
                    edi = dword[rax]
                    [rcx] = rdi
                    rdi = rax - 4
                    [rax] = esi
                    rsi = rcx + 4
                    if(rdi > rsi){
                        esi = dword[rcx + 4]
                        edi = dword[rax - 4]
                        [rcx + 4] = edi
                        rdi = rcx + 8
                        [rax - 4] = esi
                        rsi = rax - 8
                        if(rdi < rsi){
                            esi = dword[rcx + 8]
                            edi = dword[rax + 8]
                            [rcx + 8] = edi
                            [rax + 8] = esi
                        }
                    }
                }
                xmm0 = xmmword[rsp]//0x10
                xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
                //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
                //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
                [rsp] = xmm1
                xmm0 = xmm0 switch//den putter det bare op i den anden ende
                //0x0000000000000000000000000a414141
                //0x0a414141000000000000000000000000
                [rsp + 0x10] = xmm0
                //den har byttet stacken om fra før:
                //4141 410a 0000 0000 0000 0000 0000 0000
                //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
                //efter:
                //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
                //0000 0000 0000 0000 0000 0000 4141 410a
                //vær opmærksom på det er ikke tal taget fra lige den her branch
            }
        }
    }
    else{
        rdi = rax - 1
        rcx = shr(rdi, 3)
        r9 = rcx + 1
        neg rcx
        r10 = r9*4
        rcx = rax + rcx*4
        if(r10 > rcx || rdi <= 0x17){
            rax = rbx
            do while(rax < rsi){
                ecx = dword[rax]
                edi = dword[rsi]
                rax += 4
                rsi -= 4
                [rax - 4] = rdi
                [rsi + 4] = ecx
            }
            rax = *var6
            esi = 8 - dword[ByteRIP] & 7
            rdi = rbx + rsi*4
            if(rdi >= rax){
                xmm0 = xmmword[rsp]//0x10
                xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
                //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
                //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
                [rsp] = xmm1
                xmm0 = xmm0 switch//den putter det bare op i den anden ende
                //0x0000000000000000000000000a414141
                //0x0a414141000000000000000000000000
                [rsp + 0x10] = xmm0
                //den har byttet stacken om fra før:
                //4141 410a 0000 0000 0000 0000 0000 0000
                //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
                //efter:
                //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
                //0000 0000 0000 0000 0000 0000 4141 410a
                //vær opmærksom på det er ikke tal taget fra lige den her branch
            }
            else{
                r8 = rsp + 0x1b - rdi
                rcx = shr(r8, 3)
                r9 = neg(rcx)
                rsi = shl(rsi + rcx + 1, 2)
                r9 = r9*4 + 0x1c
                if(r9 >= rsi){
                    r9 = 1
                }
                else{
                    r9 = 0
                }
                rsi = *ByteRIP
                if(rdi >= rsi){
                    sil = 1
                }
                else{
                    sil = 0//det er den nederste byte af rsi
                }
                or r9b, sil
                if(r9b == 0 || r8 <= 0x17){
                    do while(rax > rdi){
                        ecx = dword[rdi]
                        esi = dword[rax]
                        rdi += 4
                        rax -= 4
                        [rdi - 4] = esi
                        [rax + 4] = ecx
                    }
                    xmm0 = xmmword[rsp]//0x10
                    xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
                    //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
                    //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
                    [rsp] = xmm1
                    xmm0 = xmm0 switch//den putter det bare op i den anden ende
                    //0x0000000000000000000000000a414141
                    //0x0a414141000000000000000000000000
                    [rsp + 0x10] = xmm0
                    //den har byttet stacken om fra før:
                    //4141 410a 0000 0000 0000 0000 0000 0000
                    //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
                    //efter:
                    //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
                    //0000 0000 0000 0000 0000 0000 4141 410a
                    //vær opmærksom på det er ikke tal taget fra lige den her branch
                }
                else{
                    r9 = rcx + 1
                    rsi = rsp + 0x10
                    rcx = rdi
                    r8 = shl(shr(r9, 2), 4) + rdi
                    do while(rcx != r8){
                        xmm0 = xmmword[rcx]//0x10 bytes
                        xmm1 = xmmword[rsi] shift//den bytter endian rundt men kun i grupper af 4 bytes
                        rcx += 0x10
                        [rcx - 0x10] = xmm1
                        rsi -= 0x10
                        xmm0 = xmm0 shift
                        [rsi + 0x10] = xmm0
                    }
                    rsi = r9
                    and rsi, 0xfffffffffffffffc
                    rcx = rdi + rsi*4
                    rdi = neg(rsi)
                    rax = rax + rdi*4
                    if(r9 != rsi){
                        esi = dword[rcx]
                        edi = dword[rax]
                        [ecx] = edi
                        rdi = rax - 4
                        [rax] = rsi
                        rsi = rcx + 4
                        if(rdi > rsi){
                            esi = dword[rcx + 4] 
                            edi = dword[rax - 4]
                            [rcx + 4] = edi
                            rdi = rcx + 8
                            [rax - 4] = esi
                            rsi = rax - 8
                            if(rdi < rsi){
                                esi = dword[rcx + 8]
                                edi = dword[rax - 8]
                                [rcx + 8] = edi
                                [rax - 8] = esi
                            }
                        }
                    }
                    xmm0 = xmmword[rsp]//0x10
                    xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
                    //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
                    //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
                    [rsp] = xmm1
                    xmm0 = xmm0 switch//den putter det bare op i den anden ende
                    //0x0000000000000000000000000a414141
                    //0x0a414141000000000000000000000000
                    [rsp + 0x10] = xmm0
                    //den har byttet stacken om fra før:
                    //4141 410a 0000 0000 0000 0000 0000 0000
                    //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
                    //efter:
                    //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
                    //0000 0000 0000 0000 0000 0000 4141 410a
                    //vær opmærksom på det er ikke tal taget fra lige den her branch
                }
            }
        }
        else{//den her er næste
            rdi = shl(shr(r9, 2), 4)
            rax = rbx + rax + 0xc
            rcx = rbx
            r11 = rax - rdi
            do while(r11 != rax){
                xmm0 = xmmword[rcx]
                xmm5 = xmmword[rax]
                rax -= 0x10
                rcx += 0x10
                pshufd xmm1, xmm5, 0x1b
                pshufd xmm0, xmm0, 0x1b
                [rcx - 0x10] = xmm1
                [rax + 0x10] = xmm0
            }
            rdi = r9 & 0xfffffffffffffffc
            rax = neg(rdi)
            rcx = rbx + rdi*4
            rax = rsi + rax*4
            if(r9 != rdi){
                [rcx] = dword[rax]
                [rax] = dword[rcx]
                if(rcx + 4 < rax - 4){
                    [rcx + 4] = dword[rax - 4]
                    [rax - 4] = dword[rcx + 4]
                    if(rax - 8 > rcx + 8){
                        [rcx + 8] = dword[rax - 8]
                        [rax - 8] = dword[rcx + 8]
                    }
                }
            }
            esi = 8 - dword[ByteRIP] & 7
            rax = *var6 
            rdi = rbx + rsi*4
            if(rdi >= rax){
                xmm0 = xmmword[rsp]//0x10
                xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
                //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
                //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
                [rsp] = xmm1
                xmm0 = xmm0 switch//den putter det bare op i den anden ende
                //0x0000000000000000000000000a414141
                //0x0a414141000000000000000000000000
                [rsp + 0x10] = xmm0
                //den har byttet stacken om fra før:
                //4141 410a 0000 0000 0000 0000 0000 0000
                //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
                //efter:
                //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
                //0000 0000 0000 0000 0000 0000 4141 410a
                //vær opmærksom på det er ikke tal taget fra lige den her branch
            }
            else{//kommet her til
                r8 = *var6 - 1 - rdi
                rcx = shr(r8, 3)
                r9 = neg(rcx)
                rsi = shl(rsi + rcx + 1, 2)
                r9 = r9*4 + 0x1c
                if(r9 >= rsi){
                    r9 = 1
                }
                else{
                    r9 = 0
                }
                rsi = *ByteRIP
                if(rdi >= rsi){
                    sil = 1                    
                }
                else{
                    sil = 0
                }
                or r9b, sil
                if(r9b == 0 || r8 <= 0x17){
                    do while(rax < rsi){
                        ecx = dword[rdi]
                        esi = dword[rax]
                        rdi += 4
                        rax -= 4
                        dword[rdi - 4] = esi
                        dword[rax + 4] = ecx
                    }
                    xmm0 = xmmword[rsp]//0x10
                    xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
                    //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
                    //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
                    [rsp] = xmm1
                    xmm0 = xmm0 switch//den putter det bare op i den anden ende
                    //0x0000000000000000000000000a414141
                    //0x0a414141000000000000000000000000
                    [rsp + 0x10] = xmm0
                    //den har byttet stacken om fra før:
                    //4141 410a 0000 0000 0000 0000 0000 0000
                    //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
                    //efter:
                    //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
                    //0000 0000 0000 0000 0000 0000 4141 410a
                    //vær opmærksom på det er ikke tal taget fra lige den her branch
                }
                else{
                    r9 = rcx + 1
                    rsi = rsp + 0x10
                    rcx = rdi
                    r8 = shl(shr(r9, 2), 4) + rdi
                    do while(rcx != r8){
                        xmm0 = xmmword[rcx]
                        pshufd(xmm1, xmmword[rsi], 0x1b)
                        rcx += 0x10
                        xmmword[rcx - 0x10] = xmm1
                        rsi -= 0x10
                        pshufd(xmm0, xmm0, 0x1b)
                        xmmword[rsi + 0x10] = xmm0
                    }
                    rsi = r9 & 0xfffffffffffffffc
                    rcx = rdi + rsi*4
                    rdi = neg(rsi)
                    rax = rax + rdi*4
                    if(r9 != rsi){
                        esi = dword[rcx]
                        edi = dword[rax]
                        dword[rcx] = edi
                        rdi = rax - 4
                        dword[rax] = esi
                        rsi = rcx + 4
                        if(rdi > rsi){
                            esi = dword[rcx + 4]
                            edi = dwrod[rax - 4]
                            dword[rcx + 4] = edi
                            rdi = rcx + 8
                            dword[rax - 4] = esi
                            rsi = rax - 8
                            if(rdi < rsi){
                                esi = dword[rcx + 8]
                                edi = dword[rax - 8]
                                dword[rcx + 8] = edi
                                dword[rax - 8] = esi
                            }
                        }
                    }
                    xmm0 = xmmword[rsp]//0x10
                    xmm1 = xmmword[rsp+0x10]//den bytter endian rundt men kun i grupper af 4 bytes
                    //00 00 00 00  a2 ba 3b 6f  86 66 a9 2e  0a 42 42 42
                    //00 00 00 00  6f 3b ba a2  2e a9 66 86  42 42 42 0a
                    [rsp] = xmm1
                    xmm0 = xmm0 switch//den putter det bare op i den anden ende
                    //0x0000000000000000000000000a414141
                    //0x0a414141000000000000000000000000
                    [rsp + 0x10] = xmm0
                    //den har byttet stacken om fra før:
                    //4141 410a 0000 0000 0000 0000 0000 0000
                    //0000 0000 6f3b baa2 2ea9 6686 4242 420a                                                                                                                             
                    //efter:
                    //4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                          
                    //0000 0000 0000 0000 0000 0000 4141 410a
                    //vær opmærksom på det er ikke tal taget fra lige den her branch
                }
            }
        }
    }
}
else{
    //bliver ikke kaldt
}









/* stack inden
4141 410a 4242 420a 2ea9 6686 6f3b baa2                                                                                                                                  
0000 0000 0000 0000 0000 0000 0000 0000

stack efter
4242 420a 2ea9 6686 6f3b baa2 0000 0000                                                                                                                                  
0000 0000 0000 0000 0000 0000 4141 410a


stack inden
4242420add94846c 6f3bbaa2f33de2ea
0000000000000000 000000004141410a

stack efter
000000004141410a 4242420add94846c                                                                                                                                  
6f3bbaa2f33de2ea 0000000000000000


stack inden
1ed6c576c8304031 42504937e32af2a3
f33de2ea00000000 86eefd2662f73fc1


stack efter
86ee fd26 62f7 3fc1 1ed6 c576 c830 4031
4250 4937 e32a f2a3 f33d e2ea 0000 0000
ok så det den gør er at stacken inden ser sådan her ud 4 blokke af 8 bytes
1                       2
3                       4
bagefter ser det sådan her ud
4                       1
2                       3
i både 3 & 2