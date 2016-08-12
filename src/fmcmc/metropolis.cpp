/**
 * @file
 *
 * @date 29.07.2016
 * @author marco@kleesiek.com
 */

#include <fmcmc/metropolis.h>
#include <fmcmc/proposal.h>

#include <algorithm>

using namespace std;

namespace fmcmc
{

MetropolisHastings::MetropolisHastings() :
    fInitialErrorScale( 1.0 ),
    fStartPointRandomization( 1.0 ),

    fBetas{ 1.0 }
{ }

MetropolisHastings::~MetropolisHastings()
{ }

bool MetropolisHastings::Initialize()
{
    Sample startPoint;
    startPoint.Values() = GetParameterConfig().GetStartValues();

    if (fBetas.empty())
        fBetas = { 1.0 };

    const size_t nChains = fBetas.size();

    // in case of parallel tempering, setup more than one chain
    fSampledChains.assign( nChains, Chain() );
    fDynamicParamConfigs.assign( nChains, fParameterConfig );

    for (auto& chain : fSampledChains) {
        Sample randomizedStartPoint = startPoint;
        chain.push_back( startPoint );
    }

    if (!fProposalFunction)
        fProposalFunction.reset( new ProposalGaussian() );

    return true;
}

double MetropolisHastings::Advance()
{

    /*

    // regular MH algorithm

    fNextStateBuffer = fCurrentState;
    const double transRatio = fProposal->Transition(fCurrentState, fNextStateBuffer);

    const double priorCurrent = GetParameterConfig().Prior(fCurrentState);
    const double priorNext = GetParameterConfig().Prior(fNextStateBuffer);

    if (priorCurrent <= 0.0)
        return 1.0;
    else if (priorNext <= 0.0)
        return 0.0;
    else {
        if (GetCurveFitter()->DoesLikelihoodFluctuate())
            UpdateNegLogLikelihood(fCurrentState);

        UpdateNegLogLikelihood(fNextStateBuffer);
        const double mhRatio = min(1.0, transRatio * priorNext/priorCurrent * exp( fBeta * (fCurrentState.GetNegLogLikelihood() - fNextStateBuffer.GetNegLogLikelihood()) ) );

//        if (fDoBurnIn && mhRatio < 1.0)
//            return 0.0;
        return mhRatio;
    }



    assert(GetParameterConfig().Size() == NumberOfParameters() && fSavedStates.Size() > 0 );

    const double acceptanceProb = NextStepProbability();

    const bool accepted = (acceptanceProb >= 1.0 || KRandom::GetInstance().Bool(acceptanceProb));

    if (accepted) {
        fCurrentState = fNextStateBuffer;
//      KDEBUG(i << ": Accepted. p=" << acceptanceProb);
    }
//    else {
//        KDEBUG(i << ": Denied. p=" << acceptanceProb);
//    }

    fCurrentState.IncrementTime();
    fNextStateBuffer.IncrementTime();

    return (accepted) ? 1.0 : 0.0;


    */

    return 0.0;
}

} /* namespace fmcmc */
