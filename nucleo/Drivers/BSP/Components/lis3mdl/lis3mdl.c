/**
 ******************************************************************************
 * @file    lis3mdl.c
 * @author  MEMS Application Team
 * @version V1.4.0
 * @date    17-September-2015
 * @brief   This file provides a set of functions needed to manage the lis3mdl.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "lis3mdl.h"
#include <math.h>

/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @addtogroup LIS3MDL
 * @{
 */

static MAGNETO_StatusTypeDef LIS3MDL_Init(MAGNETO_InitTypeDef *LIS3MDL_Init);
static MAGNETO_StatusTypeDef LIS3MDL_Read_M_ID(uint8_t *m_id);
static MAGNETO_StatusTypeDef LIS3MDL_M_GetAxes(int32_t *pData);
static MAGNETO_StatusTypeDef LIS3MDL_M_GetAxesRaw(int16_t *pData);
static MAGNETO_StatusTypeDef LIS3MDL_M_Get_ODR( float *odr );
static MAGNETO_StatusTypeDef LIS3MDL_M_Set_ODR( float odr );
static MAGNETO_StatusTypeDef LIS3MDL_M_GetSensitivity( float *pfData );
static MAGNETO_StatusTypeDef LIS3MDL_M_Get_FS( float *fullScale );
static MAGNETO_StatusTypeDef LIS3MDL_M_Set_FS( float fullScale );

/** @defgroup LIS3MDL_Private_Variables LIS3MDL_Private_Variables
 * @{
 */
MAGNETO_DrvTypeDef LIS3MDLDrv =
{
  LIS3MDL_Init,
  LIS3MDL_Read_M_ID,
  LIS3MDL_M_GetAxes,
  LIS3MDL_M_GetAxesRaw,
  LIS3MDL_M_Get_ODR,
  LIS3MDL_M_Set_ODR,
  LIS3MDL_M_GetSensitivity,
  LIS3MDL_M_Get_FS,
  LIS3MDL_M_Set_FS,
  NULL
};

/* ------------------------------------------------------- */
/* Here you should declare the variable that implements    */
/* the internal struct of extended features of LIS3MDL.    */
/* Then you must update the NULL pointer in the variable   */
/* of the extended features below.                         */
/* See the example of LSM6DS3 in lsm6ds3.c                 */
/* ------------------------------------------------------- */

MAGNETO_DrvExtTypeDef LIS3MDLDrv_ext =
{
  MAGNETO_LIS3MDL_COMPONENT, /* unique ID for LIS3MDL in the MAGNETO driver class */
  NULL /* pointer to internal struct of extended features of LIS3MDL */
};

/**
 * @}
 */

/** @defgroup LIS3MDL_Private_Functions LIS3MDL_Private_Functions
 * @{
 */

/**
 * @brief  Set LIS3MDL Initialization
 * @param  LIS3MDL_Init the configuration setting for the LIS3MDL
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_Init(MAGNETO_InitTypeDef *LIS3MDL_Init)
{
  uint8_t tmp1 = 0x00;
  
  /* Configure the low level interface ---------------------------------------*/
  if(LIS3MDL_IO_Init() != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  /****** Magnetic sensor *******/
  
  if(LIS3MDL_IO_Read(&tmp1, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG3_M, 1) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  /* Conversion mode selection */
  tmp1 &= ~(LIS3MDL_M_MD_MASK);
  tmp1 |= LIS3MDL_Init->M_OperatingMode;
  
  if(LIS3MDL_IO_Write(&tmp1, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG3_M, 1) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  if(LIS3MDL_IO_Read(&tmp1, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG1_M, 1) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  /* Output data rate selection */
  tmp1 &= ~(LIS3MDL_M_DO_MASK);
  tmp1 |= LIS3MDL_Init->M_OutputDataRate;
  
  /* X and Y axes Operative mode selection */
  tmp1 &= ~(LIS3MDL_M_OM_MASK);
  tmp1 |= LIS3MDL_Init->M_XYOperativeMode;
  
  if(LIS3MDL_IO_Write(&tmp1, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG1_M, 1) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  if(LIS3MDL_IO_Read(&tmp1, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG2_M, 1) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  /* Full scale selection */
  tmp1 &= ~(LIS3MDL_M_FS_MASK);
  tmp1 |= LIS3MDL_Init->M_FullScale;
  
  if(LIS3MDL_IO_Write(&tmp1, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG2_M, 1) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  /* Configure interrupt lines */
  LIS3MDL_IO_ITConfig();
  
  return MAGNETO_OK;
  
  /******************************/
}


/**
 * @brief  Read ID of LIS3MDL Magnetic sensor
 * @param  m_id the pointer where the ID of the device is stored
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_Read_M_ID(uint8_t *m_id)
{
  if(!m_id)
  {
    return MAGNETO_ERROR;
  }
  
  return LIS3MDL_IO_Read(m_id, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_WHO_AM_I_ADDR, 1);
}


/**
 * @brief  Read raw data from LIS3MDL Magnetic sensor output register
 * @param  pData the pointer where the magnetometer raw data are stored
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_M_GetAxesRaw(int16_t *pData)
{
  uint8_t tempReg[2] = {0, 0};
  
  if(LIS3MDL_IO_Read(&tempReg[0], LIS3MDL_M_MEMS_ADDRESS, (LIS3MDL_M_OUT_X_L_M | LIS3MDL_I2C_MULTIPLEBYTE_CMD),
                     2) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  pData[0] = ((((int16_t)tempReg[1]) << 8) + (int16_t)tempReg[0]);
  
  if(LIS3MDL_IO_Read(&tempReg[0], LIS3MDL_M_MEMS_ADDRESS, (LIS3MDL_M_OUT_Y_L_M | LIS3MDL_I2C_MULTIPLEBYTE_CMD),
                     2) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  pData[1] = ((((int16_t)tempReg[1]) << 8) + (int16_t)tempReg[0]);
  
  if(LIS3MDL_IO_Read(&tempReg[0], LIS3MDL_M_MEMS_ADDRESS, (LIS3MDL_M_OUT_Z_L_M | LIS3MDL_I2C_MULTIPLEBYTE_CMD),
                     2) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  pData[2] = ((((int16_t)tempReg[1]) << 8) + (int16_t)tempReg[0]);
  
  return MAGNETO_OK;
}


/**
 * @brief Read data from LIS3MDL Magnetic sensor and calculate Magnetic in mgauss
 * @param pData the pointer where the magnetometer data are stored
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_M_GetAxes(int32_t *pData)
{
  uint8_t tempReg = 0x00;
  int16_t pDataRaw[3];
  float sensitivity = 0;
  
  if(LIS3MDL_M_GetAxesRaw(pDataRaw) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  if(LIS3MDL_IO_Read(&tempReg, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG2_M, 1) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  tempReg &= LIS3MDL_M_FS_MASK;
  
  switch(tempReg)
  {
    case LIS3MDL_M_FS_4:
      sensitivity = 0.14;
      break;
    case LIS3MDL_M_FS_8:
      sensitivity = 0.29;
      break;
    case LIS3MDL_M_FS_12:
      sensitivity = 0.43;
      break;
    case LIS3MDL_M_FS_16:
      sensitivity = 0.58;
      break;
  }
  
  pData[0] = (int32_t)(pDataRaw[0] * sensitivity);
  pData[1] = (int32_t)(pDataRaw[1] * sensitivity);
  pData[2] = (int32_t)(pDataRaw[2] * sensitivity);
  
  return MAGNETO_OK;
}


/**
 * @brief  Read Magneto Output Data Rate
 * @param  odr the pointer where the magnetometer output data rate is stored
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_M_Get_ODR( float *odr )
{
  /*Here we have to add the check if the parameters are valid*/
  uint8_t tempReg = 0x00;
  
  if(LIS3MDL_IO_Read(&tempReg, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG1_M, 1 ) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  tempReg &= LIS3MDL_M_DO_MASK;
  
  switch( tempReg )
  {
    case LIS3MDL_M_DO_0_625:
      *odr = 0.625f;
      break;
    case LIS3MDL_M_DO_1_25:
      *odr = 1.25f;
      break;
    case LIS3MDL_M_DO_2_5:
      *odr = 2.5f;
      break;
    case LIS3MDL_M_DO_5:
      *odr = 5.0f;
      break;
    case LIS3MDL_M_DO_10:
      *odr = 10.0f;
      break;
    case LIS3MDL_M_DO_20:
      *odr = 20.0f;
      break;
    case LIS3MDL_M_DO_40:
      *odr = 40.0f;
      break;
    case LIS3MDL_M_DO_80:
      *odr = 80.0f;
      break;
    default:
      break;
  }
  
  return MAGNETO_OK;
}


/**
 * @brief  Write Magneto Output Data Rate
 * @param  odr the magnetometer output data rate to be set
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_M_Set_ODR( float odr )
{
  uint8_t new_odr = 0x00;
  uint8_t tempReg = 0x00;
  
  new_odr = ( odr <= 0.625f   ) ? LIS3MDL_M_DO_0_625
            : ( odr <= 1.25f  ) ? LIS3MDL_M_DO_1_25
            : ( odr <= 2.5f  ) ? LIS3MDL_M_DO_2_5
            : ( odr <= 5.0f ) ? LIS3MDL_M_DO_5
            : ( odr <= 10.0f ) ? LIS3MDL_M_DO_10
            : ( odr <= 20.0f ) ? LIS3MDL_M_DO_20
            : ( odr <= 40.0f ) ? LIS3MDL_M_DO_40
            :                     LIS3MDL_M_DO_80;
            
  if(LIS3MDL_IO_Read(&tempReg, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG1_M, 1 ) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  tempReg &= ~(LIS3MDL_M_DO_MASK);
  tempReg |= new_odr;
  
  if(LIS3MDL_IO_Write(&tempReg, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG1_M, 1) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  return MAGNETO_OK;
}


/**
 * @brief  Read Magneto Sensitivity
 * @param  pfData the pointer where the magnetometer sensitivity is stored
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_M_GetSensitivity( float *pfData )
{
  /*Here we have to add the check if the parameters are valid*/
  uint8_t tempReg = 0x00;
  
  if(LIS3MDL_IO_Read(&tempReg, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG2_M, 1 ) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  tempReg &= LIS3MDL_M_FS_MASK;
  
  switch( tempReg )
  {
    case LIS3MDL_M_FS_4:
      *pfData = 0.14f;
      break;
    case LIS3MDL_M_FS_8:
      *pfData = 0.29f;
      break;
    case LIS3MDL_M_FS_12:
      *pfData = 0.43f;
      break;
    case LIS3MDL_M_FS_16:
      *pfData = 0.58f;
      break;
    default:
      break;
  }
  
  return MAGNETO_OK;
}


/**
 * @brief  Read Magneto Full Scale
 * @param  fullScale the pointer where the magnetometer full scale is stored
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_M_Get_FS( float *fullScale )
{
  /*Here we have to add the check if the parameters are valid*/
  uint8_t tempReg = 0x00;
  
  if(LIS3MDL_IO_Read(&tempReg, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG2_M, 1 ) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  tempReg &= LIS3MDL_M_FS_MASK;
  
  switch( tempReg )
  {
    case LIS3MDL_M_FS_4:
      *fullScale = 4.0f;
      break;
    case LIS3MDL_M_FS_8:
      *fullScale = 8.0f;
      break;
    case LIS3MDL_M_FS_12:
      *fullScale = 12.0f;
      break;
    case LIS3MDL_M_FS_16:
      *fullScale = 16.0f;
      break;
    default:
      break;
  }
  
  return MAGNETO_OK;
}


/**
 * @brief  Write Magneto Full Scale
 * @param  fullScale the magnetometer full scale to be set
 * @retval MAGNETO_OK in case of success, an error code otherwise
 */
static MAGNETO_StatusTypeDef LIS3MDL_M_Set_FS( float fullScale )
{
  uint8_t new_fs = 0x00;
  uint8_t tempReg = 0x00;
  
  new_fs = ( fullScale <= 4.0f ) ? LIS3MDL_M_FS_4
           : ( fullScale <= 8.0f ) ? LIS3MDL_M_FS_8
           : ( fullScale <= 12.0f ) ? LIS3MDL_M_FS_12
           :                         LIS3MDL_M_FS_16;
           
  if(LIS3MDL_IO_Read(&tempReg, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG2_M, 1 ) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  tempReg &= ~(LIS3MDL_M_FS_MASK);
  tempReg |= new_fs;
  
  if(LIS3MDL_IO_Write(&tempReg, LIS3MDL_M_MEMS_ADDRESS, LIS3MDL_M_CTRL_REG2_M, 1 ) != MAGNETO_OK)
  {
    return MAGNETO_ERROR;
  }
  
  return MAGNETO_OK;
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
