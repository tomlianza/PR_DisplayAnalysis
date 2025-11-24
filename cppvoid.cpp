cpp PR_SpectroMeterDlg.cpp
void CPRSpectroMeterDlg::OnBnClickedButton3()
{
    switch (m_ToggleIndex)
    {
    case 0:
        m_pColorBox->m_RGB.sRed = 255; m_pColorBox->m_RGB.sGreen = 0; m_pColorBox->m_RGB.sBlue = 0; m_ToggleIndex++; break;
    case 1:
        m_pColorBox->m_RGB.sRed = 0; m_pColorBox->m_RGB.sGreen = 255; m_pColorBox->m_RGB.sBlue = 0; m_ToggleIndex++; break;
    case 2:
        m_pColorBox->m_RGB.sRed = 0; m_pColorBox->m_RGB.sGreen = 0; m_pColorBox->m_RGB.sBlue = 255; m_ToggleIndex++; break;
    default:
        m_pColorBox->m_RGB.sRed = 255; m_pColorBox->m_RGB.sGreen = 255; m_pColorBox->m_RGB.sBlue = 255; m_ToggleIndex = 0; break;
    }
    SendToColorBox(m_pColorBox, SHOW_COLOR, NULL);
}