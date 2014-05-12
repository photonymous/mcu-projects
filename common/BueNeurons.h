#ifndef BUE_NEURONS
#define BUE_NEURONS

#include <stdint.h>
#include <BueNetUtil.h>

//===============================================================================================
// BueNeuron Class Declaration
template <int N_BELOW, int N_WITHIN, int N_ABOVE>
class BueNeuron
{
private:
   static const uint8_t PERM_THRESH = 127;
   XORShift32* m_pRNG;
   
   uint8_t m_arrBelowPermanences[N_BELOW];   
   uint8_t m_arrWithinPermanences[N_WITHIN];   
   uint8_t m_arrAbovePermanences[N_ABOVE];
   
   uint8_t m_arrBelowWeights[N_BELOW/8];   
   uint8_t m_arrWithinWeights[N_WITHIN/8];   
   uint8_t m_arrAboveWeights[N_ABOVE/8];

public:
   BueNeuron();
   void init(XORShift32* pRNG);
   uint32_t process();
};

//---------------------------
BueNeuron::
init(XORShift32* pRNG) : 
   m_pRNG(pRNG)
{
   for(int ii = 0; ii < N_BELOW;  ii++) m_arrBelowPermanences[ii]  = m_rRNG->next8();
   for(int ii = 0; ii < N_WITHIN; ii++) m_arrWithinPermanences[ii] = m_rRNG->next8();
   for(int ii = 0; ii < N_ABOVE;  ii++) m_arrAbovePermanences[ii]  = m_rRNG->next8();
   for(int ii = 0; ii < N_BELOW;  ii++) m_arrBelowWeights[ii]      = m_arrBelowPermanences[ii]  > PERM_THRESH;
   for(int ii = 0; ii < N_WITHIN; ii++) m_arrWithinWeights[ii]     = m_arrWithinPermanences[ii] > PERM_THRESH;
   for(int ii = 0; ii < N_ABOVE;  ii++) m_arrAboveWeights[ii]      = m_arrAbovePermanences[ii]  > PERM_THRESH;
}


//--------------------------
uint32_t
BueNeuron::
process()
{
}


#endif
