#ifndef MANUAL_ADJUSTMENTS_H_INCLUDED
#define MANUAL_ADJUSTMENTS_H_INCLUDED

class CManualAdjustments
{
public:
	CManualAdjustments()
	{
		m_bCanAdjustBrightness = m_bCanAdjustContrast = m_bCanAdjustColorTemp = 
		m_bCanAdjustGains = false;
	}

	inline void SetCanAdjustBrightness(bool can) {m_bCanAdjustBrightness = can;}
	inline bool GetCanAdjustBrightness() {return m_bCanAdjustBrightness;}
	
	inline void SetCanAdjustContrast(bool can) {m_bCanAdjustContrast = can;}
	inline bool GetCanAdjustContrast() {return m_bCanAdjustContrast;}
	
	inline void SetCanAdjustColorTemp(bool can) {m_bCanAdjustColorTemp = can;}
	inline bool GetCanAdjustColorTemp() {return m_bCanAdjustColorTemp;}
	
	inline void SetCanAdjustGains(bool can) {m_bCanAdjustGains = can;}
	inline bool GetCanAdjustGains() {return m_bCanAdjustGains;}

	bool m_bCanAdjustBrightness;
	bool m_bCanAdjustContrast;
	bool m_bCanAdjustColorTemp;
	bool m_bCanAdjustGains;
};

#endif
	
