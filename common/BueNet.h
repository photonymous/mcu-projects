/* 
   Neural Network intended for 32-bit micro controllers.
   Based on ideas gathered from the Deep Learning community.
   
*/

#ifndef BUENET_H
#define BUENET_H

#include <stdint.h>

//==========================================================
// Computes the dot product between two binary vectors (up to 32-bits long).
// First computes the bit-wise "and", then counts all of the set bits.
// Used to compute the input activations of a neuron.
inline 
uint32_t 
dotProduct32(uint32_t a, uint32_t b)
{
   uint32_t p = a & b;
   p = p - ((p >> 1) & 0x55555555);
   p = (p & 0x33333333) + ((p >> 2) & 0x33333333);
   return (((p + (p >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
}


//==========================================================
// RNG Declaration
class XORShift32
{
private:
   static const int SHIFT1 = 6;
   static const int SHIFT2 = 21;
   static const int SHIFT3 = 7;
   uint32_t m_iState;
   uint32_t m_iSeed;
   
public:
   XORShift32(uint32_t iSeed) :
      m_iSeed(iSeed),
      m_iState(iSeed)
   {}
   
   inline uint32_t next()
   {
      uint32_t iRetVal = m_iState;
      m_iState = m_iState ^ (m_iState << SHIFT1);
      m_iState = m_iState ^ (m_iState >> SHIFT2);
      m_iState = m_iState ^ (m_iState << SHIFT3);
      return iRetVal;
   }
};

//==========================================================
// BueNeuron Class Declaration
template <int N_INPUTS, int N_IN_LAYER, int N_OUTPUTS>
class BueNeuron
{
private:
   uint8_t m_arrBelowPermanences[N_INPUTS];   
   uint8_t m_arrWithinPermanences[N_IN_LAYER];   
   uint8_t m_arrAbovePermanences[N_OUTPUTS];
   
   uint8_t m_arrBelowWeights[N_INPUTS/8];   
   uint8_t m_arrWithinWeights[N_IN_LAYER/8];   
   uint8_t m_arrAboveWeights[N_OUTPUTS/8];

public:
   BueNeuron();
   uint32_t process(uint8_t* arrLayer0, uint8_t* arrLayer1, uint8_t* arrLayer2);
};

//==========================================================
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
   
   // Indexed as: [neuron][permanence]
   BueNeuron<N_INPUTS, N_HIDDEN, N_HIDDEN> arrInputNeurons[N_HIDDEN];
   
   // Indexed as: [layer][neuron][permanence]
   BueNeuron<N_HIDDEN, N_HIDDEN, N_HIDDEN> arrHiddenNeurons[N_LAYERS-2][N_HIDDEN];
      
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




#endif

