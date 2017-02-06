// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        ( 0, uint256("0xf3f023de22dc6d2749844e9f62150c8cf0e3eb849392fa3914609b4c878af13c"))
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        1486339200, // * UNIX timestamp of last checkpoint block d77cb63a40042d73a83142383c7872c123cda7253db1d9c0effc8a029ca857b2
        0,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        1152.0     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0xf3f023de22dc6d2749844e9f62150c8cf0e3eb849392fa3914609b4c878af13c"))		
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1486339200, // 06022017
        0,
        630
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0x0b03fdcf0f035802aada1002031af19b4e9c7bbc069c8a2facbfb48c7dbfb35f"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("043014c67b78f95c8964ba4f10bc83ce6dbee8d6afeb0570552e2f7562f83a5ae6cc937900545ab5c30a84565315d55107d5269e816c50e4080ca89dc2cc64e9c2");
        nDefaultPort = 8644;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 210000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        nTargetTimespanx = 10 * 60; // 10 minutes
        nTargetSpacing = 2.5 * 60; // 2.5 minutes
        nMaxTipAge = 24 * 60 * 60;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * 
         * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
         *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
         *   vMerkleTree: 4a5e1e
         */
        const char* pszTimestamp = "Foreign Minister Sergey V. Lavrov of Russia, who conveyed the announcement at a news conference in Moscow, also said Russia and the United States were close to an agreement. Mon Feb 6 00:00:00 2017";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 42000000 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04a15fddd04020b22f44bb5688d5104532d93b5503ee7bcb998a334390ef584c1199267f67d324b2c6b843ab350260bde25671952299af57d084085cd2a73dfe0d") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1486339200;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 577581;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xf3f023de22dc6d2749844e9f62150c8cf0e3eb849392fa3914609b4c878af13c"));
        assert(genesis.hashMerkleRoot == uint256("0x310c5292db48bec790ee970944d31dcd14b8fbd4f61301304d10eb06e2da5b23"));
		
		vSeeds.push_back(CDNSSeedData("king.odj.ru", "king.odj.ru"));
		vSeeds.push_back(CDNSSeedData("king1.odj.ru", "king1.odj.ru"));
		vSeeds.push_back(CDNSSeedData("king2.odj.ru", "king2.odj.ru"));
		vSeeds.push_back(CDNSSeedData("king3.odj.ru", "king3.odj.ru"));

		vSeeds.push_back(CDNSSeedData("node1.exip.net", "node1.exip.net"));
		vSeeds.push_back(CDNSSeedData("node2.exip.net", "node2.exip.net"));
		vSeeds.push_back(CDNSSeedData("node3.exip.net", "node3.exip.net"));
		vSeeds.push_back(CDNSSeedData("node4.exip.net", "node4.exip.net"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(0);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(128);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        // Libracoin: Mainnet v2 enforced as of block 710k
        nEnforceV2AfterHeight = 710000;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        /*
		*pchMessageStart[0] = 0xfc;
        *pchMessageStart[1] = 0xc1;
        *pchMessageStart[2] = 0xb7;
        *pchMessageStart[3] = 0xdc;
		**/
		pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("043014c67b78f95c8964ba4f10bc83ce6dbee8d6afeb0570552e2f7562f83a5ae6cc937900545ab5c30a84565315d55107d5269e816c50e4080ca89dc2cc64e9c2");
        nDefaultPort = 9333;
        bnProofOfWorkLimit = ~uint256(0) >> 20; //empty
        nSubsidyHalvingInterval = 210000; //empty
        nEnforceBlockUpgradeMajority = 750; //51
        nRejectBlockOutdatedMajority = 950; //75
        nToCheckBlockUpgradeMajority = 1000; //100
        nMinerThreads = 0;
        nTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        nTargetTimespanx = 10 * 60; // 10 minutes
        nTargetSpacing = 2.5 * 60; // 2.5 minutes
        nMaxTipAge = 24 * 60 * 60;
        //nMaxTipAge = 0x7fffffff;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1486339200;
        genesis.nNonce = 577581;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xf3f023de22dc6d2749844e9f62150c8cf0e3eb849392fa3914609b4c878af13c"));

        vFixedSeeds.clear();
        vSeeds.clear();

		vSeeds.push_back(CDNSSeedData("king.odj.ru", "king.odj.ru"));
		vSeeds.push_back(CDNSSeedData("king1.odj.ru", "king1.odj.ru"));
		vSeeds.push_back(CDNSSeedData("king2.odj.ru", "king2.odj.ru"));
		vSeeds.push_back(CDNSSeedData("king3.odj.ru", "king3.odj.ru"));

		vSeeds.push_back(CDNSSeedData("node1.exip.net", "node1.exip.net"));
		vSeeds.push_back(CDNSSeedData("node2.exip.net", "node2.exip.net"));
		vSeeds.push_back(CDNSSeedData("node3.exip.net", "node3.exip.net"));
		vSeeds.push_back(CDNSSeedData("node4.exip.net", "node4.exip.net"));
		
        base58Prefixes[PUBKEY_ADDRESS] = list_of(48);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(5);
        base58Prefixes[SECRET_KEY] =     list_of(176);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);
		
        //base58Prefixes[PUBKEY_ADDRESS] = list_of(111);
        //base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        //base58Prefixes[SECRET_KEY]     = list_of(239);
        //base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        //base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false; //true
        fDefaultConsistencyChecks = false;
        fRequireStandard = true; //false
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false; //true

        // Libracoin: Testnet v2 enforced as of block 400k
        nEnforceV2AfterHeight = 710000;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 3.5 * 24 * 60 * 60; // 3.5 days
        nTargetTimespanx = 10 * 60; // 10 minutes
        nTargetSpacing = 2.5 * 60; // 2.5 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nMaxTipAge = 24 * 60 * 60;
        genesis.nTime = 1486339200;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 19444;
        assert(hashGenesisBlock == uint256("0xae3b5ccc6180e0974540f49db5964c33f8039b6280e09e3820d5c432c8ba7841"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        // Libracoin: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;

        // Libracoin: v2 enforced using Bitcoin's supermajority rule
        nEnforceV2AfterHeight = -1;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
