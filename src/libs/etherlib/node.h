#pragma once
/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * Copyright (c) 2017 by Great Hill Corporation.
 * All Rights Reserved
 *
 * The LICENSE at the root of this repo details your rights (if any)
 *------------------------------------------------------------------------*/

#include "etherlib.h"

namespace qblocks {

    //-----------------------------------------------------------------------
    extern bool     readOneBlock_fromJson   (      CBlock& block,   const SFString& fileName);
    extern bool     readOneBlock_fromBinary (      CBlock& block,   const SFString& fileName);
    extern void     writeToJson             (const CBaseNode& node, const SFString& fileName);
    extern void     writeToBinary           (const CBaseNode& node, const SFString& fileName);
    extern bool     verifyBlock             (const CBlock& block,   SFString& result);

    //-------------------------------------------------------------------------
    extern SFString compileSolidity         (const SFString& sol);
    extern SFString getVersionFromClient    (void);
    extern SFUint32 getLatestBlockFromClient(void);
    extern SFUint32 getLatestBlockFromCache (CSharedResource *res=NULL);
    extern SFUint32 getLatestBloomFromCache (void);
    extern bool     getLatestBlocks         (SFUint32& cache, SFUint32& client, CSharedResource *res=NULL);

    //-------------------------------------------------------------------------
    extern bool     getCode                 (const SFAddress& addr, SFString& theCode);
    inline SFString getCode                 (const SFAddress& addr) { SFString ret; getCode(addr, ret); return ret; }
    inline bool     isContract              (const SFAddress& addr) { return !getCode(addr).Substitute("0x","").empty(); }
    extern SFUintBN getBalance              (const SFAddress& addr, blknum_t blockNum, bool isDemo);
    extern bool     getSha3                 (const SFString& hexIn, SFString& shaOut);
    inline SFString getSha3                 (const SFString& hexIn) { SFString ret; getSha3(hexIn,ret); return ret; }

    //-------------------------------------------------------------------------
    extern bool     getBlock                (CBlock& block,       SFUint32 num);
    extern bool     getTransaction          (CTransaction& trans, const SFString& hash);
    extern bool     getTransaction          (CTransaction& trans, const SFString& hash, SFUint32 transID);
    extern bool     getTransaction          (CTransaction& trans, blknum_t blockNum, SFUint32 transID);
    extern bool     getReceipt              (CReceipt& receipt,   const SFString& hash);
    extern bool     getLogEntry             (CLogEntry& log,      const SFString& hash);
    extern void     getTraces               (CTraceArray& traces, const SFHash& hash);

    //-------------------------------------------------------------------------
    extern bool     queryBlock              (CBlock& block,       const SFString& num, bool needTrace);
    extern bool     queryRawBlock           (SFString& block,     const SFString& num, bool needTrace, bool hashesOnly);
    extern bool     queryRawTransaction     (const SFHash& txHash, SFString& results);
    extern bool     queryRawReceipt         (const SFHash& txHash, SFString& results);
    extern bool     queryRawLogs            (SFUint32 fromBlock, SFUint32 toBlock, const SFAddress& addr, SFString& results);
    extern bool     queryRawTrace           (SFString& trace,     const SFString& hashIn);

    //-------------------------------------------------------------------------
    extern void     etherlib_init           (const SFString& client);
    extern void     etherlib_cleanup        (void);

    //-------------------------------------------------------------------------
    extern SFString callRPC                 (const SFString& method, const SFString& params, bool raw);

    //-------------------------------------------------------------------------
    extern void     setStorageRoot          (const SFString& path);
    extern SFString getStorageRoot          (void);
    extern SFString getJsonFilename1        (SFUint32 num);
    extern SFString getBinaryFilename1      (SFUint32 num);
    extern SFString getJsonPath1            (SFUint32 num);
    extern SFString getBinaryPath1          (SFUint32 num);

    //-------------------------------------------------------------------------
    typedef bool (*BLOCKVISITFUNC)(CBlock& block, void *data);
    typedef bool (*TRANSVISITFUNC)(CTransaction& trans, void *data);

    //-------------------------------------------------------------------------
    typedef bool (*MINIBLOCKVISITFUNC)(CMiniBlock& block, const CMiniTrans *trans, void *data);
    typedef bool (*MINITRANSVISITFUNC)(CMiniTrans& trans, void *data);

    //-------------------------------------------------------------------------
    extern bool forEveryBlockOnDisc          (BLOCKVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1, SFUint32 skip=1);
    extern bool forEveryEmptyBlockOnDisc     (BLOCKVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1, SFUint32 skip=1);
    extern bool forEveryNonEmptyBlockOnDisc  (BLOCKVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1, SFUint32 skip=1);
    extern bool forEveryFullBlockIndex       (BLOCKVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1, SFUint32 skip=1);
    extern bool forEveryBlock                (BLOCKVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1, SFUint32 skip=1);
    extern bool forEveryBloomFile            (FILEVISITOR func,    void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1, SFUint32 skip=1);

    //-------------------------------------------------------------------------
    extern bool forEveryTransaction          (TRANSVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1);
    extern bool forEveryTransactionTo        (TRANSVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1);
    extern bool forEveryTransactionFrom      (TRANSVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1);

    //-------------------------------------------------------------------------
    extern bool forEveryFullBlockInMemory    (BLOCKVISITFUNC     func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1);
    extern bool forEveryMiniBlockInMemory    (MINIBLOCKVISITFUNC func, void *data, SFUint32 start=0, SFUint32 count=(SFUint32)-1);
    extern void clearInMemoryCache           (void);

    //-------------------------------------------------------------------------
    class CBlockVisitor
    {
    public:
        CBlockVisitor(SFUint32 fb, SFUint32 c) : m_firstBlock(fb), m_cnt(c) { }
        SFUint32 firstBlock() const { return m_firstBlock; }
        SFUint32 getCount() const { return m_cnt; }
        void setFirst(SFUint32 n) { m_firstBlock = n; }
        void setCount(SFUint32 n) { m_cnt = n; }

    protected:
        SFUint32 m_firstBlock;
        SFUint32 m_cnt;

    private:
        CBlockVisitor(void) : m_firstBlock(0), m_cnt(0) { }
    };

    // Syntactic Sugar (TODO: These should be removed from the library)
    //-------------------------------------------------------------------------
    inline void   forEveryBlockFromClient    (BLOCKVISITFUNC     func, CBlockVisitor *bv) { forEveryBlockOnDisc        (func, bv, bv->firstBlock(), bv->getCount()); }
    inline void   forEveryBlockOnDisc        (BLOCKVISITFUNC     func, CBlockVisitor *bv) { forEveryBlockOnDisc        (func, bv, bv->firstBlock(), bv->getCount()); }
    inline void   forEveryNonEmptyBlockOnDisc(BLOCKVISITFUNC     func, CBlockVisitor *bv) { forEveryNonEmptyBlockOnDisc(func, bv, bv->firstBlock(), bv->getCount()); }
    inline void   forEveryFullBlockInMemory  (BLOCKVISITFUNC     func, CBlockVisitor *bv) { forEveryFullBlockInMemory  (func, bv, bv->firstBlock(), bv->getCount()); }
    inline void   forEveryMiniBlockInMemory  (MINIBLOCKVISITFUNC func, CBlockVisitor *bv) { forEveryMiniBlockInMemory  (func, bv, bv->firstBlock(), bv->getCount()); }

    extern SFString blockCachePath(const SFString& _part);

#define fullBlockIndex (blockCachePath("fullBlocks.bin"))
#define miniBlockCache (blockCachePath("miniBlocks.bin"))
#define miniTransCache (blockCachePath("miniTrans.bin"))
#define blockFolder    (blockCachePath("blocks/"))
#define bloomFolder    (blockCachePath("blooms/"))

}  // namespace qblocks
