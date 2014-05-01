#ifndef BUENET_UTIL_H
#define BUENET_UTIL_H

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
   
   int m_iIndex;
   uint32_t m_iState;
   uint32_t m_iSeed;
   
public:
   XORShift32(uint32_t iSeed) :
      m_iSeed(iSeed),
      m_iState(iSeed),
      m_iIndex(0)
   {}
   
   inline uint32_t next32()
   {
      uint32_t iRetVal = m_iState;
      m_iState = m_iState ^ (m_iState << SHIFT1);
      m_iState = m_iState ^ (m_iState >> SHIFT2);
      m_iState = m_iState ^ (m_iState << SHIFT3);
      return iRetVal;
   }
   
   inline uint8_t next8()
   {
		uint8_t iRetVal = *(((uint8_t*)(&m_iState)) + m_iIndex);
		m_iIndex++;
   	if(m_iIndex == 4)
		{
			next32();
			m_iIndex = 0;
		}
		return iRetVal;
   }
};


#endif
