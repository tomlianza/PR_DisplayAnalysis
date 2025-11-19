// CMeasurementData Class used to manipulate and store measurement data
#include "stdafx.h"
#include "CMeasurementData.h"

CMeasurementData::CMeasurementData()
{


};
CMeasurementData::~CMeasurementData() {






};
bool  CMeasurementData::InterpolateTo1nmData()
{

	m_Interp.m_whichType = I_LINEAR;
	m_Interp.m_npts = (short) (1 + (m_currentMeasurement.DeviceDescriptor.dEndLamda - m_currentMeasurement.DeviceDescriptor.dStartLamda) / m_currentMeasurement.DeviceDescriptor.dLamdaIncrement);
	m_Interp.m_x = m_currentMeasurement.dWavelength;
	m_Interp.m_y = m_currentMeasurement.dNativeSpectrum;
	m_Interp.Init();
	int i,j;
	j = 0;
	for (i = (int)m_currentMeasurement.DeviceDescriptor.dStartLamda;i < m_currentMeasurement.DeviceDescriptor.dEndLamda; i++)
	{

		m_currentMeasurement.InterpolatedSpectrum[j++] = m_Interp.GetInterpolatedValue((double)i);

	}
	
	return true;
};

bool CMeasurementData::ConfigureDeviceData()
{


	return true;
};
bool CMeasurementData::ConfigureDeviceData(DEVICETYPE whichDevice, MEASUREMENTDATA *whichDataArray)
{


	return true; 
};


void CMeasurementData::SetMeasurementToReferenceDataSet(FILTERWHEELPOS whichPos, MEASUREMENTDATA *whichData)
{


}
void CMeasurementData::SetMeasurementToDeviceDataSet(FILTERWHEELPOS whichPos, MEASUREMENTDATA *whichData)
{


}
void CMeasurementData::ComputeStatistics(MEASUREMENTDATA *whichDataArray, int iMeasurements, MEASUREMENTDATA *whichDataSummary)
{

}


double CMeasurementData::ComputeStandardDeviation(double *DataArray, int nPoints)
{
	int i;
	double dMean = ComputeMean(DataArray, nPoints);
	double dSigma = 0;
	double dDif;
	for (i = 0; i < nPoints; i++)
	{
		dDif = dMean - DataArray[i];
		dSigma += dDif * dDif;

	}
	dSigma /= nPoints; 

	dSigma = pow (dSigma , 0.5);

	return dSigma;

};
double CMeasurementData::ComputeMean(double *DataArray, int nPoints)
{
	int i; 
	double dMean = 0;
	for (i = 0; i < nPoints; i++)
		dMean += DataArray[i];

	dMean /= nPoints; 
	return dMean;

};

void CMeasurementData::ComputeSimpleStats(SIMPLESTATS *m_simpleStats, SIMPLE_MEASUREMENT *smArray, int sReps)
{
	int i;
	double * TempArray = new double[sReps];

	// X statistics

	for (i = 0; i < sReps; i++)
	{
		TempArray[i] = smArray[i].XYZdatadouble.X;
	}
	m_simpleStats->Xmean = ComputeMean(TempArray, sReps);
	m_simpleStats->Xstd = ComputeStandardDeviation(TempArray, sReps);

	for (i = 0; i < sReps; i++)
	{
		TempArray[i] = smArray[i].XYZdatadouble.Y;
	}
	m_simpleStats->Ymean = ComputeMean(TempArray, sReps);
	m_simpleStats->Ystd = ComputeStandardDeviation(TempArray, sReps);

	for (i = 0; i < sReps; i++)
	{
		TempArray[i] = smArray[i].XYZdatadouble.Z;
	}
	m_simpleStats->Zmean = ComputeMean(TempArray, sReps);
	m_simpleStats->Zstd = ComputeStandardDeviation(TempArray, sReps);

	for (i = 0; i < sReps; i++)
	{
		TempArray[i] = smArray[i].dIntegrationTime;
	}
	m_simpleStats->IntTimeMean = ComputeMean(TempArray, sReps);
	m_simpleStats->IntTimeStd = ComputeStandardDeviation(TempArray, sReps);

	for (i = 0; i < sReps; i++)
	{
		TempArray[i] = smArray[i].dIntegratedEnergy;
	}
	m_simpleStats->IntegratedEnergyMean = ComputeMean(TempArray, sReps);
	m_simpleStats->IntegratedEnergyStdev = ComputeStandardDeviation(TempArray, sReps);
	// now compute summary statistics 
	m_simpleStats->LuminanceErrorPercent = 100 * ((  m_simpleStats->Ymean- m_simpleStats->dTargetLuminanceEnglish  ) / m_simpleStats->dTargetLuminanceEnglish);

	// now calculate the chromaticity data from the XYZ data
	double Xref, Yref, Zref, x_ref, y_ref;
	double Xdut, Ydut, Zdut, x_dut, y_dut;

	Xref = m_simpleStats->dTargetXYZdata.X;
	Xdut = m_simpleStats->Xmean;

	Yref = m_simpleStats->dTargetXYZdata.Y;
	Ydut = m_simpleStats->Ymean;

	Zref = m_simpleStats->dTargetXYZdata.Z;
	Zdut = m_simpleStats->Zmean;

	x_ref = Xref / (Xref + Yref + Zref);
	x_dut = Xdut / (Xdut + Ydut + Zdut);

	y_ref = Yref / (Xref + Yref + Zref);
	y_dut = Ydut / (Xdut + Ydut + Zdut);

	m_simpleStats->deltax = x_dut - x_ref;
	m_simpleStats->deltay = y_dut - y_ref;
	// to do....calcuate Delta E.  
	m_simpleStats->deltaEstar = 0; 
	m_simpleStats->dResponsivity = 1000.0/(m_simpleStats->IntegratedEnergyMean * m_simpleStats->IntTimeMean);
	m_simpleStats->dRawResponsivity = 1000 /( smArray->dIntegratedLightMinusDarkData * smArray->dIntegrationTime);
	m_simpleStats->dLumThreshold = m_simpleStats->Ystd * 10;

	delete[] TempArray;

};
bool CMeasurementData::SaveBinarySimpleStatistics(CString FilePath, SIMPLESTATS *stats)
{
	CFile cfStats;
	char * cPath = FilePath.GetBuffer();
	CFileException  cfProblem;
	CString csData, csName;
	//char cBuffer[2048];
	if (cfStats.Open(cPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &cfProblem))
	{
		cfStats.Write(stats, sizeof(SIMPLESTATS));
		cfStats.Close();
		return(true);
	}
	else
		return(false);

}
bool CMeasurementData::SaveSimpleStatisticsFile(CString FilePath,SIMPLESTATS *stats)
{

	CFile cfStats;
	char * cPath = FilePath.GetBuffer();
	CFileException  cfProblem;
	CString csData, csName;
	char cBuffer[2048];
	
	if(	cfStats.Open(cPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &cfProblem))
	{
		// Write the stats as required. 
/*
		typedef struct SimpleStats {

			double		dTargetLuminanceEnglish; // this is the target luminance for this data set 
			XYZDATA     dTargetXYZdata; // This is the target XYZ data for this data set .
			double Xmean;
			double Xstd;
			double Ymean;
			double Ystd;
			double Zmean;
			double Zstd;
			double IntTimeMean;
			double IntTimeStd;
			double IntegratedEnergyMean;
			double IntegratedEnergyStdev;
			// summary data after comparison of averages betwwn the dut and the calibration device 
			double LuminanceErrorPercent;
			double deltax;
			double deltay;
			double deltaEstar;  // used for device under test.

		}SIMPLESTATS;*/	 
		cfStats.SeekToEnd();
		
		strcpy_s(cBuffer, stats->csDescription);
		strcat_s(cBuffer, ",");
		cfStats.Write(cBuffer, strlen(cBuffer));
		sprintf_s(cBuffer, "TargetLuminance=,%8.4f," ,stats->dTargetLuminanceEnglish);
		cfStats.Write(cBuffer, strlen(cBuffer));
		sprintf_s(cBuffer, "TargetX=,%8.4f,", stats->dTargetXYZdata.X);
		cfStats.Write(cBuffer, strlen(cBuffer));
		sprintf_s(cBuffer, "TargetY=,%8.4f,", stats->dTargetXYZdata.Y);
		cfStats.Write(cBuffer, strlen(cBuffer));
		sprintf_s(cBuffer, "TargetZ=,%8.4f,", stats->dTargetXYZdata.Z);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "X mean =,%10.5f,", stats->Xmean);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "X stdev =,%10.5f,", stats->Xstd);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "Y mean =,%10.5f,", stats->Ymean);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "Ystd mean =,%10.5f,", stats->Ystd);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "Z mean =,%10.5f,", stats->Zmean);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "Z std =,%10.5f,", stats->Zstd);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "Int Time mean =,%10.5f,", stats->IntTimeMean);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "Int Time std =,%10.5f,", stats->IntTimeStd);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "IntegratedEnergyMean =,%10.5f,", stats->IntegratedEnergyMean);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "IntegratedEnergyStdev =,%10.5f,", stats->IntegratedEnergyStdev);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "LuminanceErrorPercent =,%10.5f,", stats->LuminanceErrorPercent);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "deltax =,%10.5f,", stats->deltax);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "deltay =,%10.5f,", stats->deltay);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "deltaEstar =,%10.5f,", stats->deltaEstar);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "Responsivity =,%10.5f,", stats->dResponsivity);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "RawResponsivity =,%10.5f,", stats->dRawResponsivity);
		cfStats.Write(cBuffer, strlen(cBuffer));

		sprintf_s(cBuffer, "Luminance Threshold =,%10.5f,", stats->dLumThreshold);
		cfStats.Write(cBuffer, strlen(cBuffer));


		sprintf_s(cBuffer, "\r\n");
		cfStats.Write(cBuffer, strlen(cBuffer));

		cfStats.Close();
		return(true);

	}
	else
	{
		return(false);
	}


}