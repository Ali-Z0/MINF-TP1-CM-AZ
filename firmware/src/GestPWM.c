/*--------------------------------------------------------*/
// GestPWM.c
/*--------------------------------------------------------*/
//	Description :	Gestion des PWM 
//			        pour TP1 2016-2017
//
//	Auteur 		: 	C. HUBER
//
//	Version		:	V1.1
//	Compilateur	:	XC32 V1.42 + Harmony 1.08
//
/*--------------------------------------------------------*/



#include "GestPWM.h"
#include "Mc32DriverAdc.h"
#include "APP.h"

S_pwmSettings PWMData;      // pour les settings
S_ADCResults ReadAdc;
        
void GPWM_Initialize(S_pwmSettings *pData)
{
   // Init les data 
    
   // Init �tat du pont en H
    
   // lance les timers et OC
    
}

// Obtention vitesse et angle (mise a jour des 4 champs de la structure)
void GPWM_GetSettings(S_pwmSettings *pData)	
{
    /* Gestion de la lecture d'ADC avec filtrage */
    GPWM_ReadAdcFiltered(pData);
    
    /* Calcul de la consigne de vitesse */
    pData->absSpeed = pData->adcResFilt_Can0 * SPEED_RATIO;
    pData->SpeedSetting = (float)pData->absSpeed - (float)99;
    pData->absSpeed = abs(pData->SpeedSetting);
    
    
    /* Calcul consigne de la vitesse */
    pData->absAngle = pData->adcResFilt_Can1 * (180 / ADC_RES);
    pData->AngleSetting = (float)pData->absSpeed - (float)90;
    pData->absAngle = abs(pData->AngleSetting);
    
    
    
    
    

    
    // conversion
    
}


// Affichage des information en exploitant la structure
void GPWM_DispSettings(S_pwmSettings *pData)
{
    
}

// Execution PWM et gestion moteur � partir des info dans structure
void GPWM_ExecPWM(S_pwmSettings *pData)
{
    
}

// Execution PWM software
void GPWM_ExecPWMSoft(S_pwmSettings *pData)
{
    
}

uint8_t GPWM_ReadAdcFiltered(S_pwmSettings *pData)
{
    uint8_t i = 0; 
    uint8_t flagZero = 0; 
    
    /* Si le compteur de nombre d'�chantillons pour filtrage atteint */
    if(pData->cntAdc < FILTER_SIZE)
    {
        /* Sauvegarde les cannaux dans le buffer de mesure */
        pData->AdcResBuff[pData->cntAdc] = BSP_ReadAllADC();
        /* Incremente le timer de filtrage */
        pData->cntAdc = pData->cntAdc +1;
    }
    else
    {
        /* Relance le filtrage */
        pData->cntAdc = 0;
    }
    /* Somme du buffer pour le filtrage */
    for(i = 0; i<FILTER_SIZE; i++)
    {
        pData->adcResFilt_Can0 = pData->adcResFilt_Can0 + pData->AdcResBuff[i].Chan0;
        pData->adcResFilt_Can1 = pData->adcResFilt_Can1 + pData->AdcResBuff[i].Chan1;
        
        if((pData->AdcResBuff[i].Chan0 == 0) || (pData->AdcResBuff[i].Chan1 == 0))
            flagZero = 1;
    }  
    /* Moyenne du buffer avec protection de division avec 0 */
    if((pData->adcResFilt_Can0 != 0) && (pData->adcResFilt_Can1 != 0))
    {
        pData->adcResFilt_Can0 /= FILTER_SIZE;
        pData->adcResFilt_Can1 /= FILTER_SIZE;
    }
    return flagZero;
}
