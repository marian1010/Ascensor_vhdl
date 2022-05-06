/*****************************************************************************
* Filename:          C:\hlocal\Practica5/drivers/my_lcd_v1_00_a/src/my_lcd.h
* Version:           1.00.a
* Description:       my_lcd Driver Header File
* Date:              Mon Nov 29 16:05:45 2021 (by Create and Import Peripheral Wizard)
*****************************************************************************/

#ifndef MY_LCD_H
#define MY_LCD_H

/***************************** Include Files *******************************/

#include "xbasic_types.h"
#include "xstatus.h"
#include "xil_io.h"

/************************** Constant Definitions ***************************/


/**
 * User Logic Slave Space Offsets
 */
#define MY_LCD_USER_SLV_SPACE_OFFSET (0x00000000)

/**
 * Read Packet FIFO Register/Data Space Offsets
 * -- RDFIFO_RST  : read packet fifo reset register
 * -- RDFIFO_SR   : read packet fifo status register
 * -- RDFIFO_DATA : read packet fifo data
 */
#define MY_LCD_RDFIFO_REG_SPACE_OFFSET (0x00000100)
#define MY_LCD_RDFIFO_RST_OFFSET (MY_LCD_RDFIFO_REG_SPACE_OFFSET + 0x00000000)
#define MY_LCD_RDFIFO_SR_OFFSET (MY_LCD_RDFIFO_REG_SPACE_OFFSET + 0x00000004)
#define MY_LCD_RDFIFO_DATA_SPACE_OFFSET (0x00000200)
#define MY_LCD_RDFIFO_DATA_OFFSET (MY_LCD_RDFIFO_DATA_SPACE_OFFSET + 0x00000000)

/**
 * Read Packet FIFO Masks
 * -- RDFIFO_EMPTY_MASK : read packet fifo empty condition
 * -- RDFIFO_AE_MASK    : read packet fifo almost empty condition
 * -- RDFIFO_DL_MASK    : read packet fifo deadlock condition
 * -- RDFIFO_SCL_MASK   : read packet fifo occupancy scaling enabled
 * -- RDFIFO_WIDTH_MASK : read packet fifo encoded data port width
 * -- RDFIFO_OCC_MASK   : read packet fifo occupancy
 * -- RDFIFO_RESET      : read packet fifo reset
 */
#define RDFIFO_EMPTY_MASK (0x80000000UL)
#define RDFIFO_AE_MASK (0x40000000UL)
#define RDFIFO_DL_MASK (0x20000000UL)
#define RDFIFO_SCL_MASK (0x10000000UL)
#define RDFIFO_WIDTH_MASK (0x0E000000UL)
#define RDFIFO_OCC_MASK (0x01FFFFFFUL)
#define RDFIFO_RESET (0x0000000A)

/**
 * Write Packet FIFO Register/Data Space Offsets
 * -- WRFIFO_RST  : write packet fifo reset register
 * -- WRFIFO_SR   : write packet fifo status register
 * -- WRFIFO_DATA : write packet fifo data
 */
#define MY_LCD_WRFIFO_REG_SPACE_OFFSET (0x00000300)
#define MY_LCD_WRFIFO_RST_OFFSET (MY_LCD_WRFIFO_REG_SPACE_OFFSET + 0x00000000)
#define MY_LCD_WRFIFO_SR_OFFSET (MY_LCD_WRFIFO_REG_SPACE_OFFSET + 0x00000004)
#define MY_LCD_WRFIFO_DATA_SPACE_OFFSET (0x00000400)
#define MY_LCD_WRFIFO_DATA_OFFSET (MY_LCD_WRFIFO_DATA_SPACE_OFFSET + 0x00000000)

/**
 * Write Packet FIFO Masks
 * -- WRFIFO_FULL_MASK  : write packet fifo full condition
 * -- WRFIFO_AF_MASK    : write packet fifo almost full condition
 * -- WRFIFO_DL_MASK    : write packet fifo deadlock condition
 * -- WRFIFO_SCL_MASK   : write packet fifo vacancy scaling enabled
 * -- WRFIFO_WIDTH_MASK : write packet fifo encoded data port width
 * -- WRFIFO_DREP_MASK  : write packet fifo DRE present
 * -- WRFIFO_VAC_MASK   : write packet fifo vacancy
 * -- WRFIFO_RESET      : write packet fifo reset
 */
#define WRFIFO_FULL_MASK (0x80000000UL)
#define WRFIFO_AF_MASK (0x40000000UL)
#define WRFIFO_DL_MASK (0x20000000UL)
#define WRFIFO_SCL_MASK (0x10000000UL)
#define WRFIFO_WIDTH_MASK (0x0E000000UL)
#define WRFIFO_DREP_MASK (0x01000000UL)
#define WRFIFO_VAC_MASK (0x00FFFFFFUL)
#define WRFIFO_RESET (0x0000000A)

/**************************** Type Definitions *****************************/


/***************** Macros (Inline Functions) Definitions *******************/

/**
 *
 * Write a value to a MY_LCD register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the MY_LCD device.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void MY_LCD_mWriteReg(Xuint32 BaseAddress, unsigned RegOffset, Xuint32 Data)
 *
 */
#define MY_LCD_mWriteReg(BaseAddress, RegOffset, Data) \
 	Xil_Out32((BaseAddress) + (RegOffset), (Xuint32)(Data))

/**
 *
 * Read a value from a MY_LCD register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the MY_LCD device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	Xuint32 MY_LCD_mReadReg(Xuint32 BaseAddress, unsigned RegOffset)
 *
 */
#define MY_LCD_mReadReg(BaseAddress, RegOffset) \
 	Xil_In32((BaseAddress) + (RegOffset))


/**
 *
 * Reset read packet FIFO of MY_LCD to its initial state.
 *
 * @param   BaseAddress is the base address of the MY_LCD device.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void MY_LCD_mResetReadFIFO(Xuint32 BaseAddress)
 *
 */
#define MY_LCD_mResetReadFIFO(BaseAddress) \
 	Xil_Out32((BaseAddress)+(MY_LCD_RDFIFO_RST_OFFSET), RDFIFO_RESET)

/**
 *
 * Check status of MY_LCD read packet FIFO module.
 *
 * @param   BaseAddress is the base address of the MY_LCD device.
 *
 * @return  Status is the result of status checking.
 *
 * @note
 * C-style signature:
 * 	bool MY_LCD_mReadFIFOEmpty(Xuint32 BaseAddress)
 * 	Xuint32 MY_LCD_mReadFIFOOccupancy(Xuint32 BaseAddress)
 *
 */
#define MY_LCD_mReadFIFOEmpty(BaseAddress) \
 	((Xil_In32((BaseAddress)+(MY_LCD_RDFIFO_SR_OFFSET)) & RDFIFO_EMPTY_MASK) == RDFIFO_EMPTY_MASK)
#define MY_LCD_mReadFIFOOccupancy(BaseAddress) \
 	(Xil_In32((BaseAddress)+(MY_LCD_RDFIFO_SR_OFFSET)) & RDFIFO_OCC_MASK)

/**
 *
 * Read 32 bit data from MY_LCD read packet FIFO module.
 *
 * @param   BaseAddress is the base address of the MY_LCD device.
 * @param   DataOffset is the offset from the data port to read from.
 *
 * @return  Data is the data from the read packet FIFO.
 *
 * @note
 * C-style signature:
 * 	Xuint32 MY_LCD_mReadFromFIFO(Xuint32 BaseAddress, unsigned DataOffset)
 *
 */
#define MY_LCD_mReadFromFIFO(BaseAddress, DataOffset) \
 	Xil_In32((BaseAddress) + (MY_LCD_RDFIFO_DATA_OFFSET) + (DataOffset))

/**
 *
 * Reset write packet FIFO of MY_LCD to its initial state.
 *
 * @param   BaseAddress is the base address of the MY_LCD device.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void MY_LCD_mResetWriteFIFO(Xuint32 BaseAddress)
 *
 */
#define MY_LCD_mResetWriteFIFO(BaseAddress) \
 	Xil_Out32((BaseAddress)+(MY_LCD_WRFIFO_RST_OFFSET), WRFIFO_RESET)

/**
 *
 * Check status of MY_LCD write packet FIFO module.
 *
 * @param   BaseAddress is the base address of the MY_LCD device.
 *
 * @return  Status is the result of status checking.
 *
 * @note
 * C-style signature:
 * 	bool MY_LCD_mWriteFIFOFull(Xuint32 BaseAddress)
 * 	Xuint32 MY_LCD_mWriteFIFOVacancy(Xuint32 BaseAddress)
 *
 */
#define MY_LCD_mWriteFIFOFull(BaseAddress) \
 	((Xil_In32((BaseAddress)+(MY_LCD_WRFIFO_SR_OFFSET)) & WRFIFO_FULL_MASK) == WRFIFO_FULL_MASK)
#define MY_LCD_mWriteFIFOVacancy(BaseAddress) \
 	(Xil_In32((BaseAddress)+(MY_LCD_WRFIFO_SR_OFFSET)) & WRFIFO_VAC_MASK)

/**
 *
 * Write 32 bit data to MY_LCD write packet FIFO module.
 *
 * @param   BaseAddress is the base address of the MY_LCD device.
 * @param   DataOffset is the offset from the data port to write to.
 * @param   Data is the value to be written to write packet FIFO.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void MY_LCD_mWriteToFIFO(Xuint32 BaseAddress, unsigned DataOffset, Xuint32 Data)
 *
 */
#define MY_LCD_mWriteToFIFO(BaseAddress, DataOffset, Data) \
 	Xil_Out32((BaseAddress) + (MY_LCD_WRFIFO_DATA_OFFSET) + (DataOffset), (Xuint32)(Data))

/************************** Function Prototypes ****************************/


/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the MY_LCD instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus MY_LCD_SelfTest(void * baseaddr_p);

#endif /** MY_LCD_H */
