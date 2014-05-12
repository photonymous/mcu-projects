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
#include <BueNeurons.h>


//===============================================================================================
// BueNet Class Declaration
//
//   N_LAYERS  should be 3 or greater, typically 3 - 6, includes input and output layer
//   N_INPUTS  should be 2 or greater, typically 4 - 16
//   N_OUTPUTS should be 1 or greater, typically 2 - 8
//   N_HIDDEN  should be 2 or greater, typically 8 - 32
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
   BueNeuron<N_HIDDEN, N_HIDDEN, N_OUTPUTS> arrOutputNeurons[N_HIDDEN];
   
   int m_iInputRate;
   int m_iRateReduction;
   
public:
   BueNet32();
   
   void init(int iInputRate, int iRateReduction);

   void process(uint8_t* arrInputs, uint8_t* arrOutputs);

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

