
unsigned int static KimotoGravityWell(const CBlockIndex* pindexLast, const CBlockHeader *pblock, uint64 TargetBlocksSpacingSeconds, uint64 PastBlocksMin, uint64 PastBlocksMax) {
        /* current difficulty formula, megacoin - kimoto gravity well */
        const CBlockIndex *BlockLastSolved = pindexLast;
        const CBlockIndex *BlockReading = pindexLast;
        const CBlockHeader *BlockCreating = pblock;
        BlockCreating = BlockCreating;
        uint64 PastBlocksMass = 0;
        int64 PastRateActualSeconds = 0;
        int64 PastRateTargetSeconds = 0;
        double PastRateAdjustmentRatio = double(1);
        CBigNum PastDifficultyAverage;
        CBigNum PastDifficultyAveragePrev;
        double EventHorizonDeviation;
        double EventHorizonDeviationFast;
        double EventHorizonDeviationSlow;

    if (BlockLastSolved == NULL || BlockLastSolved->nHeight == 0 || (uint64)BlockLastSolved->nHeight < PastBlocksMin) { return bnProofOfWorkLimit.GetCompact(); }

        for (unsigned int i = 1; BlockReading && BlockReading->nHeight > 0; i++) {
                if (PastBlocksMax > 0 && i > PastBlocksMax) { break; }
                PastBlocksMass++;

                if (i == 1) { PastDifficultyAverage.SetCompact(BlockReading->nBits); }
                else { PastDifficultyAverage = ((CBigNum().SetCompact(BlockReading->nBits) - PastDifficultyAveragePrev) / i) + PastDifficultyAveragePrev; }
                PastDifficultyAveragePrev = PastDifficultyAverage;

                PastRateActualSeconds = BlockLastSolved->GetBlockTime() - BlockReading->GetBlockTime();
                PastRateTargetSeconds = TargetBlocksSpacingSeconds * PastBlocksMass;
                PastRateAdjustmentRatio = double(1);
                if (PastRateActualSeconds < 0) { PastRateActualSeconds = 0; }
                if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0) {
 		PastRateAdjustmentRatio = double(PastRateTargetSeconds) / double(PastRateActualSeconds);
                }
                EventHorizonDeviation = 1 + (0.7084 * pow((double(PastBlocksMass)/double(28.2)), -1.228));
                EventHorizonDeviationFast = EventHorizonDeviation;
                EventHorizonDeviationSlow = 1 / EventHorizonDeviation;

                if (PastBlocksMass >= PastBlocksMin) {
                        if ((PastRateAdjustmentRatio <= EventHorizonDeviationSlow) || (PastRateAdjustmentRatio >= EventHorizonDeviationFast)) { assert(BlockReading); break; }
                }
                if (BlockReading->pprev == NULL) { assert(BlockReading); break; }
                BlockReading = BlockReading->pprev;
        }

        CBigNum bnNew(PastDifficultyAverage);
        if (PastRateActualSeconds != 0 && PastRateTargetSeconds != 0) {
                bnNew *= PastRateActualSeconds;
                bnNew /= PastRateTargetSeconds;
        }
    if (bnNew > bnProofOfWorkLimit) { bnNew = bnProofOfWorkLimit; }

    return bnNew.GetCompact();
}
