/* 
   Neural Network intended for 32-bit micro controllers.
   Based on ideas gathered from the Deep Learning community.
   
   The network size is governed by N_INPUTS, N_HIDDEN and N_OUTPUTS.
   All layers have N_HIDDEN neurons, except the top layer, which has N_OUTPUTS neurons.
   The bottom layer connects to N_INPUTS inputs.
*/

#ifndef BUE_NET_H
#define BUE_NET_H

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
   int32_t process();
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
int32_t
BueNeuron::
process()
{
}


//===============================================================================================
// BueNet Class Declaration
//
//   N_LAYERS  should be 3 or greater, typically 3 - 6, includes input and output layer
//   N_INPUTS  should be 2 or greater, typically 4 - 16
//   N_OUTPUTS should be 1 or greater, typically 2 - 8
//   N_HIDDEN  should be 2 or greater, typically 32
template <int N_LAYERS, int N_INPUTS, int N_HIDDEN, int N_OUTPUTS>
class BueNet32
{
private:   
   XORShift32 m_theRNG;
   int        m_iRateReduction;
   uint8_t*   m_arrInputs;
   uint8_t*   m_arrOutputs;
      
   // Indexed as: [neuron][permanence]
   BueNeuron<N_INPUTS, N_HIDDEN, N_HIDDEN> m_arrInputNeurons[N_HIDDEN];
   
   // Indexed as: [layer][neuron][permanence]
   BueNeuron<N_HIDDEN, N_HIDDEN, N_HIDDEN> m_arrHiddenNeurons[N_LAYERS-2][N_HIDDEN];
      
   // Indexed as: [neuron][permanence]
   // Pulls inputs from 2 layers below, 1 layer below, and from within own layer
   BueNeuron<N_HIDDEN, N_HIDDEN, N_OUTPUTS> m_arrOutputNeurons[N_OUTPUTS];
   
public:
   BueNet32(int iInputRate, int iRateReduction, uint8_t* arrInputs, uint8_t* arrOutputs);
   void process();
};


//-------------------------------------------------------------------------------------
BueNet32::
BueNet32(int iRateReduction, uint8_t* arrInputs, uint8_t* arrOutputs, uint32_t iSeed) :
   m_theRNG(iSeed),
   m_iRateReduction(iRateReduction),
   m_arrInputs(arrInputs),
   m_arrOutputs(arrOutputs)
{
   for(int ii = 0; ii < N_HIDDEN; ii++) 
      m_arrInputNeurons[ii].init(&m_theRNG);
      
   for(int ii = 0; ii < N_LAYERS-2; ii++) 
      for(int jj = 0; jj < N_HIDDEN; jj++)
         m_arrHiddenNeurons[ii][jj].init(&m_theRNG);
      
   for(int ii = 0; ii < N_OUTPUTS; ii++) 
      m_arrOutputNeurons[ii].init(&m_theRNG);
}

//------------------
void process()
{
}



#endif

