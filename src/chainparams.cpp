// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2016 The Auroracoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"
#include "scrypt.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

//unsigned int pnSeed[] =
//{
//    0xA2F39055, 0x5EF2E56F, 0x57D54ADA, 0x50F812B0, 0x256187D5
//};

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        pchMessageStart[0] = 0xfe;
        pchMessageStart[1] = 0xb5;
        pchMessageStart[2] = 0xeb;
        pchMessageStart[3] = 0x7d;
        vAlertPubKey = ParseHex("04d1832d7d0c59634d67d3023379403014c2878d0c2372d175219063a48fa06e6d429e09f36d3196ec544c2cfdd12d6fe510a399595f75ebb6da238eb5f70f2072");
        nDefaultPort = 1280;
        nRPCPort = 1550;

        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 20); // 1.00000000
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_GROESTL] = CBigNum(~uint256(0) >> 20); // 0.00195311
        bnProofOfWorkLimit[ALGO_SKEIN]   = CBigNum(~uint256(0) >> 20); // 0.00195311
        bnProofOfWorkLimit[ALGO_QUBIT]   = CBigNum(~uint256(0) >> 20); // 0.00097655

        // Build the genesis block.
        const char* pszTimestamp = "The Times of India 29/Dec/2016 Note ban - What to expect after December 30: 10 important points";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CBigNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("0407b1b1122611bdb3bac2b3fad7f49fa34e95adc25417788c91383789bea3c708b7f42663ff9dc6840c5bf140b8d25785f182401b9a141e879b747a2cd866888a") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1483350149;
        //genesis.nBits    = Params().ProofOfWorkLimit(ALGO_SCRYPT).GetCompact();
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce   = 2061560;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0x835db5516bda09fad931f83db836c8c0314c4d0facf0590df0bf95ea324005c6"));
        assert(genesis.hashMerkleRoot == uint256("0xa49b103136f2ec85945c0a731d507549c026cb4ba84f418e5b42351a350f9407"));

        //vSeeds.push_back(CDNSSeedData("luxembourgh", "s1.auroraseed.net"));
        //vSeeds.push_back(CDNSSeedData("united-states-west", "aurseed1.criptoe.com"));
        //vSeeds.push_back(CDNSSeedData("united-states-east", "s1.auroraseed.com"));
        //vSeeds.push_back(CDNSSeedData("iceland", "s1.auroraseed.org"));
        //vSeeds.push_back(CDNSSeedData("the-netherlands", "s1.auroraseed.eu"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(38);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY]     = list_of(166);
        //base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        //base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);
        // Convert the pnSeeds array into usable address objects.
        //for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        //{
        //    const int64_t nOneWeek = 7*24*60*60;
        //    struct in_addr ip;
        //    memcpy(&ip, &pnSeed[i], sizeof(ip));
        //    CAddress addr(CService(ip, GetDefaultPort()));
        //    addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        //    vFixedSeeds.push_back(addr);
        //}
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    //virtual const vector<CAddress>& FixedSeeds() const {
    //    return vFixedSeeds;
    //}
protected:
    CBlock genesis;
    //vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    SelectParams(CChainParams::MAIN);
    return true;
}
