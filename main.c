/*
 * GccApplication10a.c
 *
 * Created: 4/3/2020 8:08:20 AM
 * Author : tungh
 */ 

#include "header_0.h"

int main(void)
{
    
	// TH: 16MHz external crystal deployed in Lab 11.
	// TH: Device Programming (Option: Fuses == Ext. Crystal Osc. 8.0- MHz; Start-up Time: 16K CK + 65ms).

	val=0;

	// TH: initializes UART.
	uart_init_();

	// TH: initializes TWI interface.
	TWIinit();

	// TH: initializes AS7262.
	as7262_init_();

	// TH: initializes pin change interrupt.
	PCinit();

	// TH: initializes TIMER 1.
	TC1init();

	// TH: initializes SPI module.
	spi_init_();

	// TH: initializes display.
	display_init_();

	// TH: enables interrupts globally.
	SREG  |= (1<<SREG_I);
	
	/////////////////////////////////////////////////////
	
	// TH: writes particular pattern to display.
	write_pattern_0_();

	/////////////////////////////////////////////////////
	
	// TH: initializes coordinates.

	row_s_high_=ST77XX_ROW_S_HIGH_;
	row_s_low_ =ST77XX_ROW_S_LOW_MIN_;
	row_e_high_=ST77XX_ROW_E_HIGH_;
	row_e_low_ =row_s_low_+6;

	col_s_high_=ST77XX_COL_S_HIGH_;
	col_s_low_ =ST77XX_COL_S_LOW_MIN_ ;
	col_e_high_=ST77XX_COL_E_HIGH_;
	col_e_low_ =col_s_low_+4;

	/////////////////////////////////////////////////////

	/*
	// TH: writes next row.
	for(uint8_t index=0; index<ROW_MAX_7_BY_5_; index++){
		write_row_portrait_(index%26, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	}//for index.
	*/

	/*
	write_row_portrait_(26, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(27, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(28, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(29, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(30, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(31, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(32, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(33, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(34, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	write_row_portrait_(35, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	*/
	
	/*
	char * ptr_str_ = "VERSION";
	write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	
	uint32_t number_ = 0x12345678;
	write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
	*/
	
	/////////////////////////////////////////////////////

	if(DEBUG_TFT_CTC_==1){
		// TH: 16MHz, no pre-scaling.
		TCCR1B |= (1<<CS10);
	}//if DEBUG_TFT_CTC_.

	// TH: polls interrupts.
    while (1){
		
		if(val==H_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Hardware Version Started.");

			{
				PCprint("\n[Lab 11]: Device Type: ");

				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_HW_VERSION_LOW_);

				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "DEVICE";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_low_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			{
				PCprint("\n[Lab 11]: Hardware Version: ");

				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_HW_VERSION_HIGH_);

				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "HARDWARE";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_low_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Hardware Version Ended.");
			val = 0;

		}//if H_CHAR_.

		else if(val==F_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Firmware Version Started.");

			// TH: experimental: disables LED control.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
			);

			{
				PCprint("\n[Lab 11]: Low Address Byte: ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_FW_VERSION_LOW_);

				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				//ptr_str_ = "FIRMWARELOW";
				//write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_low_;
				//write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			}

			{
				PCprint("\n[Lab 11]: High Address Byte: ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_FW_VERSION_HIGH_);

				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "FIRMWARE";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  |= (((uint32_t)hw_low_)<<8);
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Firmware Version Ended.");
			val = 0;

		}//if F_CHAR_.
		
		else if(val==C_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Control Register Started.");

			// TH: experimental: disables LED control.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
			);

			{
				PCprint("\n[Lab 11]: Control Setup: ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);

				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "CONTROLREG";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_low_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Control Register Ended.");
			val = 0;

		}//if C_CHAR_.

		else if(val==I_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Integration Time Started.");

			// TH: experimental: disables LED control.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
			);

			{
				PCprint("\n[Lab 11]: Integration Time: ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_INT_T_);

				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "INTEGRATION";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_low_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Integration Time Ended.");
			val = 0;

		}//if I_CHAR_.

		else if(val==T_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Temperature Started.");

			// TH: experimental: disables LED control.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
			);

			{
				PCprint("\n[Lab 11]: Device Temperature: ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_DEVICE_TEMP_);

				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "DEVICETEMP";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_low_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.


			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Temperature Ended.");
			val = 0;

		}//if T_CHAR_.

		else if(val==L_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read LED Control Started.");

			// TH: experimental: disables LED control.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
			);

			{
				PCprint("\n[Lab 11]: LED Control: ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_LED_CONTROL_);

				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "LEDCONTROL";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_low_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read LED Control Ended.");
			val = 0;

		}//if L_CHAR_.

		else if(val==V_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw V Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}
			/*
			{
				PCprint("\n[Lab 11]: Raw V Low:  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Raw V High: ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_HIGH_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}
			*/
			{
				PCprint("\n[Lab 11]: Raw V: ");

				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t  hw_low_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);
				uint8_t  hw_high_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_HIGH_);
				uint16_t hw_all_  = (((uint16_t)hw_low_)<<8) | ((uint16_t)hw_high_);

				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				uint8_t i;
				char tmpstr[10];
				sprintf(tmpstr, "0x%04x", hw_all_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "VRAW";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw V Ended.");
			val = 0;

		}//if V_CHAR_.

		else if(val==A_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated V Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}
			/*
			{
				PCprint("\n[Lab 11]: Calibrated V Address 0:  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_0_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Calibrated V Address 1:  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_1_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Calibrated V Address 2:  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_2_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Calibrated V Address 3:  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_3_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}
			*/
			{
				PCprint("\n[Lab 11]: Calibrated V: ");

				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t hw_0_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_0_);
				uint8_t hw_1_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_1_);
				uint8_t hw_2_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_2_);
				uint8_t hw_3_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_3_);

				uint32_t hw_all_ = (((uint32_t)hw_0_)<<24) | (((uint32_t)hw_1_)<<16) | (((uint32_t)hw_2_)<<8) | (((uint32_t)hw_3_)<<0);
				
				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				{
					uint8_t i;
					char tmpstr[20];
					sprintf(tmpstr, "0x%08lx", hw_all_);
					i=0;
					while(tmpstr[i]) uart_send_(tmpstr[i++]);
				}

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "VCAL";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				PCprint("\n[Lab 11]: Calibrated V (float): ");
				
				// TH: converts hex to float.
				hw_all__ = convert_hex_to_float_(hw_all_);
				print_calibrated_(hw_all__);
				
				ptr_str_ = "VCAL FLOAT";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) floor(hw_all__);
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated V Ended.");
			val = 0;

		}//if A_CHAR_.

		else if(val==B_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw B Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Raw B: ");
				
				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t  hw_low_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_RAW_LOW_);
				uint8_t  hw_high_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_RAW_HIGH_);
				uint16_t hw_all_  = (((uint16_t)hw_low_)<<8) | ((uint16_t)hw_high_);

				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				uint8_t i;
				char tmpstr[10];
				sprintf(tmpstr, "0x%04x", hw_all_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "BRAW";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw B Ended.");
			val = 0;

		}//if B_CHAR_.

		else if(val==D_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated B Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Calibrated B: ");

				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t hw_0_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_CAL_ADDR_0_);
				uint8_t hw_1_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_CAL_ADDR_1_);
				uint8_t hw_2_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_CAL_ADDR_2_);
				uint8_t hw_3_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_CAL_ADDR_3_);
				
				uint32_t hw_all_ = (((uint32_t)hw_0_)<<24) | (((uint32_t)hw_1_)<<16) | (((uint32_t)hw_2_)<<8) | (((uint32_t)hw_3_)<<0);
				
				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				{
					uint8_t i;
					char tmpstr[20];
					sprintf(tmpstr, "0x%08lx", hw_all_);
					i=0;
					while(tmpstr[i]) uart_send_(tmpstr[i++]);
				}

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "BCAL";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				PCprint("\n[Lab 11]: Calibrated B (float): ");
				
				// TH: converts hex to float.
				hw_all__ = convert_hex_to_float_(hw_all_);
				print_calibrated_(hw_all__);
				
				ptr_str_ = "BCAL FLOAT";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) floor(hw_all__);
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated B Ended.");
			val = 0;

		}//if D_CHAR_.

		else if(val==G_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw G Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Raw G: ");
				
				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t  hw_low_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_RAW_LOW_);
				uint8_t  hw_high_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_RAW_HIGH_);
				uint16_t hw_all_  = (((uint16_t)hw_low_)<<8) | ((uint16_t)hw_high_);

				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				uint8_t i;
				char tmpstr[10];
				sprintf(tmpstr, "0x%04x", hw_all_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "GRAW";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw G Ended.");
			val = 0;

		}//if G_CHAR_.

		else if(val==E_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated G Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Calibrated G: ");

				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t hw_0_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_CAL_ADDR_0_);
				uint8_t hw_1_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_CAL_ADDR_1_);
				uint8_t hw_2_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_CAL_ADDR_2_);
				uint8_t hw_3_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_CAL_ADDR_3_);
				
				uint32_t hw_all_ = (((uint32_t)hw_0_)<<24) | (((uint32_t)hw_1_)<<16) | (((uint32_t)hw_2_)<<8) | (((uint32_t)hw_3_)<<0);
				
				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				{
					uint8_t i;
					char tmpstr[20];
					sprintf(tmpstr, "0x%08lx", hw_all_);
					i=0;
					while(tmpstr[i]) uart_send_(tmpstr[i++]);
				}

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "GCAL";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				PCprint("\n[Lab 11]: Calibrated G (float): ");
				
				// TH: converts hex to float.
				hw_all__ = convert_hex_to_float_(hw_all_);
				print_calibrated_(hw_all__);
				
				ptr_str_ = "GCAL FLOAT";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) floor(hw_all__);
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated G Ended.");
			val = 0;

		}//if E_CHAR_.

		else if(val==Y_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw Y Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Raw Y: ");
				
				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t  hw_low_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_RAW_LOW_);
				uint8_t  hw_high_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_RAW_HIGH_);
				uint16_t hw_all_  = (((uint16_t)hw_low_)<<8) | ((uint16_t)hw_high_);

				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				uint8_t i;
				char tmpstr[10];
				sprintf(tmpstr, "0x%04x", hw_all_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "YRAW";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw Y Ended.");
			val = 0;

		}//if Y_CHAR_.

		else if(val==J_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated Y Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Calibrated Y: ");

				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t hw_0_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_0_);
				uint8_t hw_1_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_1_);
				uint8_t hw_2_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_2_);
				uint8_t hw_3_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_3_);
				
				uint32_t hw_all_ = (((uint32_t)hw_0_)<<24) | (((uint32_t)hw_1_)<<16) | (((uint32_t)hw_2_)<<8) | (((uint32_t)hw_3_)<<0);
				
				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				{
					uint8_t i;
					char tmpstr[20];
					sprintf(tmpstr, "0x%08lx", hw_all_);
					i=0;
					while(tmpstr[i]) uart_send_(tmpstr[i++]);
				}
				
				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "YCAL";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				PCprint("\n[Lab 11]: Calibrated Y (float): ");
				
				// TH: converts hex to float.
				hw_all__ = convert_hex_to_float_(hw_all_);
				print_calibrated_(hw_all__);
				
				ptr_str_ = "YCAL FLOAT";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) floor(hw_all__);
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated Y Ended.");
			val = 0;

		}//if J_CHAR_.

		else if(val==O_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw O Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Raw O: ");
				
				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t  hw_low_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_RAW_LOW_);
				uint8_t  hw_high_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_RAW_HIGH_);
				uint16_t hw_all_  = (((uint16_t)hw_low_)<<8) | ((uint16_t)hw_high_);

				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				uint8_t i;
				char tmpstr[10];
				sprintf(tmpstr, "0x%04x", hw_all_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "ORAW";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw O Ended.");
			val = 0;

		}//if O_CHAR_.

		else if(val==K_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated O Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Calibrated O: ");

				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t hw_0_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_CAL_ADDR_0_);
				uint8_t hw_1_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_CAL_ADDR_1_);
				uint8_t hw_2_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_CAL_ADDR_2_);
				uint8_t hw_3_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_CAL_ADDR_3_);
				
				uint32_t hw_all_ = (((uint32_t)hw_0_)<<24) | (((uint32_t)hw_1_)<<16) | (((uint32_t)hw_2_)<<8) | (((uint32_t)hw_3_)<<0);
				
				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				{
					uint8_t i;
					char tmpstr[20];
					sprintf(tmpstr, "0x%08lx", hw_all_);
					i=0;
					while(tmpstr[i]) uart_send_(tmpstr[i++]);
				}

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "OCAL";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				PCprint("\n[Lab 11]: Calibrated O (float): ");
				
				// TH: converts hex to float.
				hw_all__ = convert_hex_to_float_(hw_all_);
				print_calibrated_(hw_all__);
				
				ptr_str_ = "OCAL FLOAT";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) floor(hw_all__);
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated O Ended.");
			val = 0;

		}//if K_CHAR_.

		else if(val==R_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw R Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Raw R: ");
				
				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t  hw_low_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_RAW_LOW_);
				uint8_t  hw_high_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_RAW_HIGH_);
				uint16_t hw_all_  = (((uint16_t)hw_low_)<<8) | ((uint16_t)hw_high_);

				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				uint8_t i;
				char tmpstr[10];
				sprintf(tmpstr, "0x%04x", hw_all_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "RRAW";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw R Ended.");
			val = 0;

		}//if R_CHAR_.

		else if(val==M_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated R Started.");

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (Before): ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			{
				PCprint("\n[Lab 11]: Calibrated R: ");

				// TH: turns TFT LCD OFF for now.
				timer1_OC1A_disabled_low_();

				// TH: experimental: high current limit.
				// TH: up to 100mA -> more precise.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
				| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
				);

				// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
				as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

				// TH: waits for sensor data to be ready.
				while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

				// TH: reads virtual register.
				uint8_t hw_0_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_CAL_ADDR_0_);
				uint8_t hw_1_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_CAL_ADDR_1_);
				uint8_t hw_2_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_CAL_ADDR_2_);
				uint8_t hw_3_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_CAL_ADDR_3_);

				uint32_t hw_all_ = (((uint32_t)hw_0_)<<24) | (((uint32_t)hw_1_)<<16) | (((uint32_t)hw_2_)<<8) | (((uint32_t)hw_3_)<<0);
				
				// TH: experimental: disables LED control.
				as7262_write_virtual_(
				I2C_AS72XX_VIRTUAL_LED_CONTROL_,
				I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
				);

				{
					uint8_t i;
					char tmpstr[20];
					sprintf(tmpstr, "0x%08lx", hw_all_);
					i=0;
					while(tmpstr[i]) uart_send_(tmpstr[i++]);
				}

				// TH: lits TFT LCD unconditionally.
				timer1_OC1A_disabled_high_();

				ptr_str_ = "RCAL";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) hw_all_;
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				PCprint("\n[Lab 11]: Calibrated R (float): ");
				
				// TH: converts hex to float.
				hw_all__ = convert_hex_to_float_(hw_all_);
				print_calibrated_(hw_all__);
				
				ptr_str_ = "RCAL FLOAT";
				write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				number_  = (uint32_t) floor(hw_all__);
				write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

				// TH: starts TIMER 1 for power considerations.
				TC1init();

				if(DEBUG_TFT_CTC_==1){
					// TH: 16MHz, no pre-scaling.
					TCCR1B |= (1<<CS10);
				}//if DEBUG_TFT_CTC_.

			}

			if(DEBUG_){
				PCprint("\n[Lab 11]: Control Setup (After):  ");
				// TH: reads virtual register.
				uint8_t hw_low_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_);
				uint8_t i;
				char tmpstr[5];
				sprintf(tmpstr, "0x%02x", hw_low_);
				i=0;
				while(tmpstr[i]) uart_send_(tmpstr[i++]);
			}

			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated R Ended.");
			val = 0;

		}//if M_CHAR_.

		else if(val==N_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw ALL Started.");

			uint8_t  hw_low_v_  = 0;
			uint8_t  hw_high_v_ = 0;
			uint16_t hw_all_v_  = 0;
			uint8_t  hw_low_b_  = 0;
			uint8_t  hw_high_b_ = 0;
			uint16_t hw_all_b_  = 0;
			uint8_t  hw_low_g_  = 0;
			uint8_t  hw_high_g_ = 0;
			uint16_t hw_all_g_  = 0;
			uint8_t  hw_low_y_  = 0;
			uint8_t  hw_high_y_ = 0;
			uint16_t hw_all_y_  = 0;
			uint8_t  hw_low_o_  = 0;
			uint8_t  hw_high_o_ = 0;
			uint16_t hw_all_o_  = 0;
			uint8_t  hw_low_r_  = 0;
			uint8_t  hw_high_r_ = 0;
			uint16_t hw_all_r_  = 0;

			// TH: turns TFT LCD OFF for now.
			timer1_OC1A_disabled_low_();

			// TH: experimental: high current limit.
			// TH: up to 100mA -> more precise.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
			| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
			| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
			| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
			);

			// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
			while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
			as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);

			// TH: waits for sensor data to be ready.
			while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

			// TH: reads virtual register.
			hw_low_v_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_LOW_);
			hw_high_v_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_RAW_HIGH_);
			hw_all_v_  = (((uint16_t)hw_low_v_)<<8) | ((uint16_t)hw_high_v_);

			// TH: reads virtual register.
			hw_low_b_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_RAW_LOW_);
			hw_high_b_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_RAW_HIGH_);
			hw_all_b_  = (((uint16_t)hw_low_b_)<<8) | ((uint16_t)hw_high_b_);

			// TH: reads virtual register.
			hw_low_g_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_RAW_LOW_);
			hw_high_g_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_RAW_HIGH_);
			hw_all_g_  = (((uint16_t)hw_low_g_)<<8) | ((uint16_t)hw_high_g_);

			// TH: reads virtual register.
			hw_low_y_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_RAW_LOW_);
			hw_high_y_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_RAW_HIGH_);
			hw_all_y_  = (((uint16_t)hw_low_y_)<<8) | ((uint16_t)hw_high_y_);

			// TH: reads virtual register.
			hw_low_o_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_RAW_LOW_);
			hw_high_o_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_RAW_HIGH_);
			hw_all_o_  = (((uint16_t)hw_low_o_)<<8) | ((uint16_t)hw_high_o_);

			// TH: reads virtual register.
			hw_low_r_  = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_RAW_LOW_);
			hw_high_r_ = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_RAW_HIGH_);
			hw_all_r_  = (((uint16_t)hw_low_r_)<<8) | ((uint16_t)hw_high_r_);

			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			// TH: experimental: disables LED control.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
			);

			// TH: lits TFT LCD unconditionally.
			timer1_OC1A_disabled_high_();

			ptr_str_ = "VRAW";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_v_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			ptr_str_ = "BRAW";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_b_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			ptr_str_ = "GRAW";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_g_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			ptr_str_ = "YRAW";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_y_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			ptr_str_ = "ORAW";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_o_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			ptr_str_ = "RRAW";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_r_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			// TH: starts TIMER 1 for power considerations.
			TC1init();

			if(DEBUG_TFT_CTC_==1){
				// TH: 16MHz, no pre-scaling.
				TCCR1B |= (1<<CS10);
			}//if DEBUG_TFT_CTC_.

			if(DEBUG_) PCprint("\n[Lab 11]: Read Raw ALL Ended.");
			val = 0;

		}//if N_CHAR_.

		else if(val==P_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated ALL Started.");

			uint8_t  hw_0_v_    = 0;
			uint8_t  hw_1_v_    = 0;
			uint8_t  hw_2_v_    = 0;
			uint8_t  hw_3_v_    = 0;
			uint32_t hw_all_v_  = 0;
			uint8_t  hw_0_b_    = 0;
			uint8_t  hw_1_b_    = 0;
			uint8_t  hw_2_b_    = 0;
			uint8_t  hw_3_b_    = 0;
			uint32_t hw_all_b_  = 0;
			uint8_t  hw_0_g_    = 0;
			uint8_t  hw_1_g_    = 0;
			uint8_t  hw_2_g_    = 0;
			uint8_t  hw_3_g_    = 0;
			uint32_t hw_all_g_  = 0;
			uint8_t  hw_0_y_    = 0;
			uint8_t  hw_1_y_    = 0;
			uint8_t  hw_2_y_    = 0;
			uint8_t  hw_3_y_    = 0;
			uint32_t hw_all_y_  = 0;
			uint8_t  hw_0_o_    = 0;
			uint8_t  hw_1_o_    = 0;
			uint8_t  hw_2_o_    = 0;
			uint8_t  hw_3_o_    = 0;
			uint32_t hw_all_o_  = 0;
			uint8_t  hw_0_r_    = 0;
			uint8_t  hw_1_r_    = 0;
			uint8_t  hw_2_r_    = 0;
			uint8_t  hw_3_r_    = 0;
			uint32_t hw_all_r_  = 0;

			// TH: turns TFT LCD OFF for now.
			timer1_OC1A_disabled_low_();

			// TH: experimental: high current limit.
			// TH: up to 100mA -> more precise.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_11_
			| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
			| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
			| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
			);

			// TH: discards previous integration: DATA_RDY gets cleared when at least one sensor register been read.
			while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );
			as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_0_);
			
			// TH: waits for sensor data to be ready.
			while( (as7262_read_virtual_(I2C_AS72XX_VIRTUAL_CONTROL_) & I2C_AS72XX_VIRTUAL_CONTROL_DATA_RDY_) == 0 );

			// TH: reads virtual register.
			hw_0_v_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_0_);
			hw_1_v_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_1_);
			hw_2_v_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_2_);
			hw_3_v_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_V_CAL_ADDR_3_);
			hw_all_v_ = (((uint32_t)hw_0_v_)<<24) | (((uint32_t)hw_1_v_)<<16) | (((uint32_t)hw_2_v_)<<8) | (((uint32_t)hw_3_v_)<<0);

			// TH: reads virtual register.
			hw_0_b_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_CAL_ADDR_0_);
			hw_1_b_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_CAL_ADDR_1_);
			hw_2_b_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_CAL_ADDR_2_);
			hw_3_b_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_B_CAL_ADDR_3_);
			hw_all_b_ = (((uint32_t)hw_0_b_)<<24) | (((uint32_t)hw_1_b_)<<16) | (((uint32_t)hw_2_b_)<<8) | (((uint32_t)hw_3_b_)<<0);

			// TH: reads virtual register.
			hw_0_g_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_CAL_ADDR_0_);
			hw_1_g_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_CAL_ADDR_1_);
			hw_2_g_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_CAL_ADDR_2_);
			hw_3_g_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_G_CAL_ADDR_3_);
			hw_all_g_ = (((uint32_t)hw_0_g_)<<24) | (((uint32_t)hw_1_g_)<<16) | (((uint32_t)hw_2_g_)<<8) | (((uint32_t)hw_3_g_)<<0);

			// TH: reads virtual register.
			hw_0_y_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_0_);
			hw_1_y_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_1_);
			hw_2_y_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_2_);
			hw_3_y_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_Y_CAL_ADDR_3_);
			hw_all_y_ = (((uint32_t)hw_0_y_)<<24) | (((uint32_t)hw_1_y_)<<16) | (((uint32_t)hw_2_y_)<<8) | (((uint32_t)hw_3_y_)<<0);

			// TH: reads virtual register.
			hw_0_o_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_CAL_ADDR_0_);
			hw_1_o_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_CAL_ADDR_1_);
			hw_2_o_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_CAL_ADDR_2_);
			hw_3_o_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_O_CAL_ADDR_3_);
			hw_all_o_ = (((uint32_t)hw_0_o_)<<24) | (((uint32_t)hw_1_o_)<<16) | (((uint32_t)hw_2_o_)<<8) | (((uint32_t)hw_3_o_)<<0);

			// TH: reads virtual register.
			hw_0_r_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_CAL_ADDR_0_);
			hw_1_r_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_CAL_ADDR_1_);
			hw_2_r_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_CAL_ADDR_2_);
			hw_3_r_   = as7262_read_virtual_(I2C_AS72XX_VIRTUAL_R_CAL_ADDR_3_);
			hw_all_r_ = (((uint32_t)hw_0_r_)<<24) | (((uint32_t)hw_1_r_)<<16) | (((uint32_t)hw_2_r_)<<8) | (((uint32_t)hw_3_r_)<<0);

			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			// TH: experimental: disables LED control.
			as7262_write_virtual_(
			I2C_AS72XX_VIRTUAL_LED_CONTROL_,
			I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
			);

			// TH: lits TFT LCD unconditionally.
			timer1_OC1A_disabled_high_();

			/*
			ptr_str_ = "VCAL";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_v_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			*/
			// TH: converts hex to float.
			hw_all__ = convert_hex_to_float_(hw_all_v_);
			ptr_str_ = "VCAL FLOAT";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) floor(hw_all__);
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			/*
			ptr_str_ = "BCAL";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_b_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			*/
			// TH: converts hex to float.
			hw_all__ = convert_hex_to_float_(hw_all_b_);
			ptr_str_ = "BCAL FLOAT";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) floor(hw_all__);
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			/*
			ptr_str_ = "GCAL";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_g_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			*/
			// TH: converts hex to float.
			hw_all__ = convert_hex_to_float_(hw_all_g_);
			ptr_str_ = "GCAL FLOAT";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) floor(hw_all__);
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			/*
			ptr_str_ = "YCAL";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_y_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			*/
			// TH: converts hex to float.
			hw_all__ = convert_hex_to_float_(hw_all_y_);
			ptr_str_ = "YCAL FLOAT";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) floor(hw_all__);
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			/*
			ptr_str_ = "OCAL";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_o_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			*/
			// TH: converts hex to float.
			hw_all__ = convert_hex_to_float_(hw_all_o_);
			ptr_str_ = "OCAL FLOAT";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) floor(hw_all__);
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			/*
			ptr_str_ = "RCAL";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) hw_all_r_;
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			*/
			// TH: converts hex to float.
			hw_all__ = convert_hex_to_float_(hw_all_r_);
			ptr_str_ = "RCAL FLOAT";
			write_row_text_(ptr_str_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
			number_  = (uint32_t) floor(hw_all__);
			write_row_number_(number_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

			;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

			// TH: starts TIMER 1 for power considerations.
			TC1init();

			if(DEBUG_TFT_CTC_==1){
				// TH: 16MHz, no pre-scaling.
				TCCR1B |= (1<<CS10);
			}//if DEBUG_TFT_CTC_.

			if(DEBUG_) PCprint("\n[Lab 11]: Read Calibrated ALL Ended.");
			val = 0;

		}//if P_CHAR_.

		else if(val==Q_CHAR_){
			
			if(DEBUG_) PCprint("\n[Lab 11]: Write Pattern 0 Started.");

			// TH: lits TFT LCD unconditionally.
			timer1_OC1A_disabled_high_();

			write_pattern_0_();

			// TH: initializes coordinates.

			row_s_high_=ST77XX_ROW_S_HIGH_;
			row_s_low_ =ST77XX_ROW_S_LOW_MIN_;
			row_e_high_=ST77XX_ROW_E_HIGH_;
			row_e_low_ =row_s_low_+6;

			col_s_high_=ST77XX_COL_S_HIGH_;
			col_s_low_ =ST77XX_COL_S_LOW_MIN_ ;
			col_e_high_=ST77XX_COL_E_HIGH_;
			col_e_low_ =col_s_low_+4;

			// TH: starts TIMER 1 for power considerations.
			TC1init();

			if(DEBUG_TFT_CTC_==1){
				// TH: 16MHz, no pre-scaling.
				TCCR1B |= (1<<CS10);
			}//if DEBUG_TFT_CTC_.

			if(DEBUG_) PCprint("\n[Lab 11]: Write Pattern 0 Ended.");
			val = 0;

		}//if Q_CHAR_.

		;

	}//while 1.

}//main.

void uart_init_(void){
	
	// TH: assigns USART baud rate.
	UBRR0 = MYUBRR;

	// TH: enables 2x speed transmission mode.
	UCSR0A |= (1 << U2X0);

	// TH: enables the receiver, the transmitter, and the receiver complete interrupt.
	UCSR0B |= (1<<RXEN0)  | (1<<TXEN0) | (1<<RXCIE0);

	// TH: selects asynchronous USART, disables parity, 1 stop bit, 8-bit character, transmits on rising edge, receives on falling edge.
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00) /*| (1<<USBS0)*/; // 8bit, 1sb or 2sb

	return;

}//uart_init_.

// TH: handles UART receive complete interrupt.
ISR(USART0_RX_vect){
	
	// TH: waits until unread data can be loaded in the receive buffer.
	while ( !(UCSR0A & (1<<RXC0)) );

	// TH: reads received data.
	val = ((uint8_t) UDR0);

	return;

}//USART0_RX_vect.

void uart_send_(uint8_t data){
	
	// TH: waits for previous transmission to complete.
	while( !( UCSR0A & (1<<UDRE0)) );

	// TH: initiates new transmission.
	UDR0 = data;

	/*
	// TH: waits for previous transmission to complete.
	while( !( UCSR0A & (1<<UDRE0)) );
	*/

	return;

}//uart_send_.

void PCprint(char * strbuf){
	uint8_t i=0;
	while(strbuf[i]!='\0') uart_send_(strbuf[i++]); // Keep sending until char='\0'
}

void TWIinit(){
	
	// SETUP I2C:
//	VIN: 5V.
//	GND: GND.
//	SCL: PC0 --- pull-up already provided.
//	SDA: PC1 --- pull-up already provided.
//	RST: PA1 (output).
//	INT: PA0 (pull-up enabled).

	// TH: 14.3.7 DDRA – Port A Data Direction Register
	// TH: 14.3.6 PORTA – Port A Data Register
	// TH: sets PA1 as output (i.e. AS7262 RST).
	DDRA  |=  (1<<DDA1);

	// TH: 21.5.2 Bit Rate Generator unit
	// TH: 21.9.1 TWBR – TWI Bit Rate Register
	// TH: 21.9.3 TWSR – TWI Status Register
	// TH: sets SCL frequency to 400kHz // 32kHz.
	TWBR  = 0x0C; // 0x78;
	TWSR &= (~(1<<TWPS1)) & (~(1<<TWPS0));

	// TH: 21.9.2 TWCR – TWI Control Register
	// TH: enables TWI interrupt.
//	TWCR |= (1<<TWIE);

	// TH: 21.9.2 TWCR – TWI Control Register
	// TH: enables TWI module: SCL, SDA activated.
	TWCR |= (1<<TWEN);

}//TWIinit.

void PCinit(){
	
	// TH: 14.3.7 DDRA – Port A Data Direction Register
	// TH: 14.3.6 PORTA – Port A Data Register
	// TH: sets PORTA0 as input, with pull-up enabled.
	DDRA &= ~(1<<DDA0); PORTA |= (1<<PORTA0);

	// TH: disables pin change interrupts (groups).
	PCICR  &= (~(1<<PCIE0)) ;

	// TH: enables pin change interrupts (individual, 0).
	PCMSK0 |= (1<<PCINT0) ;

	// TH: enables pin change interrupts (groups).
	PCICR  |= (1<<PCIE0) ;
	
	;

}//PCinit.

void as7262_init_(void){
	
	// TH: as7262_init_
	PORTA &= ~(1<<PORTA1);
	_delay_ms(101);
	PORTA |=  (1<<PORTA1);

	// TH: this delay is critical for success !!
	_delay_ms(1000);

	/*
	// IMPORTANT: low current limit.
	as7262_write_virtual_(I2C_AS72XX_VIRTUAL_LED_CONTROL_,I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_);
	*/

	// TH: experimental: high current limit.
	// TH: 50mA max with power supply from AVR Dragon board when both TFT LCD and LED turned ON at the same time.
	as7262_write_virtual_(
		I2C_AS72XX_VIRTUAL_LED_CONTROL_,
		I2C_AS72XX_VIRTUAL_LED_CONTROL_ICL_DRV_10_
		| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_DRV_
		| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_11_
		| I2C_AS72XX_VIRTUAL_LED_CONTROL_LED_IND_
	);

	/*
	// TH: experimental -> low power, less precise.
	as7262_write_virtual_(I2C_AS72XX_VIRTUAL_INT_T_,I2C_AS72XX_VIRTUAL_INT_T_VALUE_7F_);
	*/

}//as7262_init_.

uint8_t as7262_read_virtual_(uint8_t virtual_){
	
	volatile uint8_t status_, d_;

	while (1){
		
		// TH: reads slave I²C status to see if the read buffer is ready.
		status_ = i2cm_read(I2C_AS72XX_SLAVE_ADDR_REG_STATUS_);
		
		if ((status_ & (1<<I2C_AS72XX_SLAVE_STATUS_TX_VALID_)) == 0) break;
		_delay_us(1);
		
	}//while 1.

	i2cm_write(I2C_AS72XX_SLAVE_ADDR_REG_WRITE_, virtual_);

	while (1){
		
		// TH: reads slave I²C status to see if the read buffer is ready.
		status_ = i2cm_read(I2C_AS72XX_SLAVE_ADDR_REG_STATUS_);

		if ((status_ & (1<<I2C_AS72XX_SLAVE_STATUS_RX_VALID_)) != 0) break;
		_delay_us(1);

	}//while 1.

	d_ = i2cm_read(I2C_AS72XX_SLAVE_ADDR_REG_READ_);

	return d_;

}//as7262_read_virtual_.

uint8_t i2cm_read(uint8_t slave_reg_){
	
	// TH: issues START condition transmission and waits for completion.
	TWIstart();

	// TH: issues slave address and access request command byte.
	TWIwrite(I2C_AS72XX_SLAVE_ADDR_WRITE_, TW_MT_SLA_ACK);

	// TH: original.
	// TH: selects slave register.
	TWIwrite(slave_reg_, TW_MT_DATA_ACK);

	// TH: experimental.
//	TWIwrite(slave_reg_, TW_MT_SLA_ACK);

	// TH: experimental.
	TWIstop();

	// TH: issues [REPEAT] START condition transmission and waits for completion.
	TWIstart();

	// TH: issues slave address and access request command byte.
	TWIwrite(I2C_AS72XX_SLAVE_ADDR_READ_, TW_MR_SLA_ACK);

	// TH: reads data from slave register.
	uint8_t data_ = TWIread_nack( TW_MR_DATA_NACK );

	// TH: issues STOP condition transmission and waits for completion.
	TWIstop();

	return data_;

}//i2cm_read.

void TWIstart(void){
	
	// TH: original.
	// TH: issues START condition transmission.
	TWCR &= (~(1<<TWSTO));
	TWCR |= (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);

	// TH: experimental.
//	TWCR = 0xA4;

	// TH: waits for completion of TWI operation.
	while (!(TWCR & (1<<TWINT)));

	// TH: logs error message.
	if ((TWSR & 0xF8) !=  TW_START) {
//		PCprint("\n[Lab 11]: TWIstart Failed.");
		exit(1);
//		errPtr= sprintf(errCode+errPtr, "START_ERROR TWSR=0x%x;\r\n", (TWSR & 0xF8));
	}//if error.
	
	return;

}//TWIstart.

void TWIwrite(uint8_t data, uint8_t expected){
	
	// TH: experimental.
	// TH: loads DATA into TWDR.
	TWDR = data;

	// TH: issues DATA transmission.
	TWCR &= (~(1<<TWSTA)) & (~(1<<TWSTO));
	TWCR |=   (1<<TWINT)  |   (1<<TWEN);

	// TH: waits for completion of TWI operation.
	// TH: waits for data to arrive on read.
	while (!(TWCR & (1<<TWINT)));

	// TH: logs error message.
	if ((TWSR & 0xF8) !=  expected) {
//		PCprint("\n[Lab 11]: TWIwrite Failed.");
		exit(1);
//		errPtr= sprintf(errCode+errPtr, "WRITE_ERROR TWSR=0x%x;\r\n", (TWSR & 0xF8));
	}//if error.

}//TWIwrite.

void TWIstop(void){
	
	// TH: experimental.
	_delay_ms(1);

	// TH: issues STOP condition transmission.
	TWCR |=   (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	// TH: experimental.
	_delay_ms(1);

	// TH: waits for completion of TWI operation.
	while ( TWCR & (1<<TWSTO) );

	return;

}//TWIstop.

uint8_t TWIread_nack(uint8_t expected){
	
	// TH: experimental.
	// TH: returns NACK when data received in Master Receiver mode.
	TWCR &= (~(1<<TWSTA)) & (~(1<<TWSTO))  & (~(1<<TWEA));
	TWCR |=   (1<<TWINT)  |   (1<<TWEN);
	

	// TH: waits until TWCR.TWINT is set.
	while (!(TWCR & (1<<TWINT)));

	// TH: reads received DATA.
	uint8_t data = TWDR;

	// TH: waits for completion of TWI operation.
	while (!(TWCR & (1<<TWINT)));

	// TH: logs error message.
	if ((TWSR & 0xF8) !=  expected) {
//		PCprint("\n[Lab 11]: TWIread_nack Failed.");
		exit(1);
//		errPtr= sprintf(errCode+errPtr, "READ_ERROR TWSR=0x%x;\r\n", (TWSR & 0xF8));
	}//if error.

	return data;

}//TWIread_nack.

void i2cm_write(uint8_t reg_write_, uint8_t reg_virtual_){
	
	// TH: issues START condition transmission and waits for completion.
	TWIstart();

	// TH: issues slave address and access request command byte.
	TWIwrite(I2C_AS72XX_SLAVE_ADDR_WRITE_, TW_MT_SLA_ACK);

	// TH: original.
	// TH: selects slave register.
	TWIwrite(reg_write_,   TW_MT_DATA_ACK);

	// TH: experimental.
//	TWIwrite(reg_write_,   TW_MT_SLA_ACK);

	// TH: uploads data.
	TWIwrite(reg_virtual_, TW_MT_DATA_ACK);

	// TH: issues STOP  condition transmission and waits for completion.
	TWIstop();

	return;

}//i2cm_write.

float convert_hex_to_float_(uint32_t hex_){
	
	double sign_     = (double)( ( hex_ & ( ((uint32_t)1)<<31 ) ) >> 31);

	float temp_ = 1; uint8_t bit_ = 0;
	for(uint32_t i=1; i<=23; i++){
		bit_ = (uint8_t)(((uint32_t)(hex_ & (1<< (23-i) ))) >> (23-i) );
		temp_ += (float)bit_ * (((float)1)/((float)pow(2,i)));
	}//for i.
	
	double exponent_ = (double)( ( hex_ & ( ((uint32_t)0xFF)<<23 ) ) >> 23);

	float float_ = 0;
	
	if(sign_==1) float_ = (float)( (-1) * temp_ * pow(2,exponent_-127) );
	else         float_ = (float)( ( 1) * temp_ * pow(2,exponent_-127));

	return float_;

}//convert_hex_to_float_.

void print_calibrated_(float hw_all__){

	uint32_t hw_all_t_= (uint32_t) floor(hw_all__);
	uint8_t i;
	char tmpstr[32];
	sprintf(tmpstr, "0x%02x%02x%02x%02x", (uint8_t)(hw_all_t_>>24),(uint8_t)(hw_all_t_>>16),(uint8_t)(hw_all_t_>>8),(uint8_t)(hw_all_t_>>0));
	i=0;
	while(tmpstr[i]) uart_send_(tmpstr[i++]);

}

void spi_init_(void){
	
	// SETUP SPI:
//	PB7 (SCK)                                ---   TFT:SCK                  ---   PULL-UP (5V, 22k).
//	PB6 (MISO)     --- PULL-UP (3.3V, 22k)   ---   NC (TFT:MISO, SD-Card)   ---   .
//	PB5 (MOSI)                               ---   TFT:MOSI                 ---   PULL-UP (5V, 22k).
//	PB4 (SS_BAR)                             ---   TFT:TFT_CS               ---   .
//	PA2 (OUTPUT)                             ---   TFT:RST                  ---   .
//	PA3 (OUTPUT)                             ---   TFT:DC                   ---   .
//	NC                                       ---   TFT:SDCS                 ---   5V.
//	PD5 (OC1A)                               ---   TFT:LIT                  ---   PULL-UP (5V, 22k).

	// TH: sets Port A: Pin X as output.
	DDRA   |=   (1<<DDA2)   | (1<<DDA3);
	PORTA  |=   (1<<PORTA2) | (1<<PORTA3);

	// TH: sets MOSI, SCK, SS_BAR as output.
	DDRB  |=    (1<<DDB5)   |   (1<<DDB7)    |   (1<<DDB4);
	PORTB &= (~(1<<PORTB5)) & (~(1<<PORTB7)) ;
	PORTB |=                                     (1<<PORTB4);

	// TH: sets MISO as input with external pull-up (3.3V).
	DDRB  &= (~(1<<DDB6));
	PORTB &= (~(1<<PORTB6));

	// TH: original.
	// TH: disables 2X speed mode.
//	SPSR0 &= (~(1<<SPI2X0));

	// TH: experimental.
	// TH: enables 2X speed mode.
	SPSR0 |= (1<<SPI2X0);

	// TH: original.
	// TH: selects LSB-1st transmission, master mode, SCK frequency (div 128).
//	SPCR0 |= (1<<DORD0) | (1<<MSTR0) | (1<<SPR10) | (1<<SPR00);

	// TH: experimental.
	// TH: selects LSB-1st transmission, master mode, SCK frequency (div 4).
	SPCR0 |=   (1<<DORD0)  |   (1<<MSTR0);
	SPCR0 &= (~(1<<SPR10)) & (~(1<<SPR00));

	// TH: shifts MSB first.
	SPCR0 &= (~((1<<DORD0)));

	// TH: disables SPI interrupt; disables SPI module; selects leading edge: rising edge, sample; falling edge: trailing edge, setup.
	SPCR0 &= (~(1<<SPIE0)) & (~(1<<SPE0)) & (~(1<<CPOL0)) & (~(1<<CPHA0));

	// TH: enables SPI module.
	SPCR0 |= (1<<SPE0);

	return;

}//spi_init_.

void TC1init(void){
	
	if(DEBUG_TFT_CTC_==0) return;

	// TH: sets Port D: Pin X as output.
	DDRD   |=   (1<<DDD5);
	PORTD  &= (~(1<<PORTD5)) ;

	// TH: initially Timer is STOPPED.
	TCCR1B &= (~(1<<CS12)) & (~(1<<CS11)) & (~(1<<CS10));

	// TH: experimental.
	// TH: CTC operation (i.e. counts up, matches at OCR1A, restarts at BOTTOM==0x0, sets OC1A).
	TCCR1A |=   (1<<COM1A1)  |    (1<<COM1A0);
	TCCR1A &= (~(1<<WGM11))  &  (~(1<<WGM10));
	TCCR1B |=   (1<<WGM12);

	// TH: helps enable Output Compare Match A Interrupt Enable (i.e. OCF1A set in TIFR1).
	TIMSK1 |= (1<<OCIE1A);

	// TH: loads initial value for Timer/Counter 1.
	TCNT1  = 0x00;

	// TH: loads OCR1A, 16-bit.
	OCR1A  = TIMER1_MAX;
	
	// TH: clears CTC flag manually.
	TIFR1  |= (1<<OCF1A);

	timer1_resolution=0;

}//TC1init.

ISR(TIMER1_COMPA_vect){
	
	if(DEBUG_TFT_CTC_==0) return;

	// TH: checks if 10 seconds have elapsed.
	if(timer1_resolution<TIMER1_TARGET_CTC_10SEC){
		timer1_resolution++; return;
	}//if less than.

	/*
	// TH: toggles LED6 with OC1A, original.
	// TH: LED must have been turned  ON already, arms  low for next compare match.
	// TH: LED must have been turned OFF already, arms high for next compare match.
	if(led6==0) { led6=1; TCCR1A &= (~(1<<COM1A0)) ; }//if led.
	else        { led6=0; TCCR1A |=   (1<<COM1A0)  ; }//else.
	*/

	// TH: experimental.
	// TH: sets or clears on next match.
//	TCCR1A ^= (1<<COM1A0);

	// TH: stops TIMER 1, disables OC1A, drives PORT low manually.
	timer1_OC1A_disabled_low_();

	// TH: experimental: disables LED control.
	as7262_write_virtual_(
	I2C_AS72XX_VIRTUAL_LED_CONTROL_,
	I2C_AS72XX_VIRTUAL_LED_CONTROL_DEFAULT_
	);

	// TH: resets timer resolution.
	timer1_resolution=0;

}//TIMER1_COMPA_vect.

void ST7735S_init_(void){
	
	// TH: hard resets ST7735S.
	PORTA  &= (~(1<<PORTA2)) ;
	_delay_us(11);
	PORTA  |=   (1<<PORTA2) ;
	_delay_ms(121);

}//ST7735S_init_.

void display_init_(void){
	
	// TH: initializes ST7735S.
	ST7735S_init_();

	// TH: pulls out of sleep mode.
	spi_write_seq_cmd_(ST77XX_SLPOUT);
	_delay_ms(121);
	
	// TH: turns display OFF.
	spi_write_seq_cmd_(ST77XX_DISPOFF);
	
	// TH: specifies interface pixel format, 18 bits per pixel.
	spi_write_seq_cmd_param_(ST77XX_COLMOD,ST77XX_COLMOD_18_);
	
	// TH: specifies display data direction.
	// 9.11.4 Frame Data Write Direction According to the MADCTL Parameters (MV, MX and MY)
	spi_write_seq_cmd_param_(ST77XX_MADCTL,ST77XX_MADCTL_MX|ST77XX_MADCTL_MY);

	// TH: turns display ON.
	spi_write_seq_cmd_(ST77XX_DISPON);
	
	;

}//display_init_.

void spi_write_seq_cmd_(uint8_t cmd_){
	
	// TH: sets D/C bit for command.
	PORTA  &= (~(1<<PORTA3));

	// TH: enables byte-shifting (i.e. pulls CS_BAR low).
	PORTB  &= (~(1<<PORTB4));
	
	// TH: starts SPI clock generator.
	SPDR0 = cmd_;

	// TH: waits for any previous transmission to complete.
	while ( !(SPSR0 & (1<<SPIF0)) );

	// TH: disables byte-shifting (i.e. pulls CS_BAR high).
	PORTB  |= (1<<PORTB4);

}//spi_write_seq_cmd_.

void spi_write_seq_cmd_param_(uint8_t cmd_, uint8_t data_){
	
	// TH: sets D/C bit for command.
	PORTA  &= (~(1<<PORTA3));

	// TH: enables byte-shifting (i.e. pulls CS_BAR low).
	PORTB  &= (~(1<<PORTB4));
	
	// TH: starts SPI clock generator.
	SPDR0 = cmd_;

	// TH: waits for any previous transmission to complete.
	while ( !(SPSR0 & (1<<SPIF0)) );

	// TH: disables byte-shifting (i.e. pulls CS_BAR high).
	PORTB  |= (1<<PORTB4);

	// TH: sets D/C bit for data.
	PORTA  |= (1<<PORTA3);

	// TH: enables byte-shifting (i.e. pulls CS_BAR low).
	PORTB  &= (~(1<<PORTB4));
	
	// TH: starts SPI clock generator.
	SPDR0 = data_;

	// TH: waits for any previous transmission to complete.
	while ( !(SPSR0 & (1<<SPIF0)) );

	// TH: disables byte-shifting (i.e. pulls CS_BAR high).
	PORTB  |= (1<<PORTB4);

}//spi_write_seq_cmd_param_.

void spi_write_seq_data_(uint8_t data_){
	
	// TH: sets D/C bit for data.
	PORTA  |= (1<<PORTA3);

	// TH: enables byte-shifting (i.e. pulls CS_BAR low).
	PORTB  &= (~(1<<PORTB4));
	
	// TH: starts SPI clock generator.
	SPDR0 = data_;

	// TH: waits for any previous transmission to complete.
	while ( !(SPSR0 & (1<<SPIF0)) );

	// TH: disables byte-shifting (i.e. pulls CS_BAR high).
	PORTB  |= (1<<PORTB4);

}//spi_write_seq_data_.

void write_pattern_0_(void){
	
	// TH: sets column window.
	spi_write_seq_cmd_(ST77XX_CASET);

	// TH: sends high byte and low byte for start column.
	spi_write_seq_data_(ST77XX_COL_S_HIGH_);
	spi_write_seq_data_(ST77XX_COL_S_LOW_ );

	// TH: sends high byte and low byte for end column.
	spi_write_seq_data_(ST77XX_COL_E_HIGH_);
	spi_write_seq_data_(ST77XX_COL_E_LOW_MAX_THEORECTICAL_);

	// TH: sets row window.
	spi_write_seq_cmd_(ST77XX_RASET);

	// TH: sends high byte and low byte for start row.
	spi_write_seq_data_(ST77XX_ROW_S_HIGH_);
	spi_write_seq_data_(ST77XX_ROW_S_LOW_ );

	// TH: sends high byte and low byte for end row.
	spi_write_seq_data_(ST77XX_ROW_E_HIGH_);
	spi_write_seq_data_(ST77XX_ROW_E_LOW_MAX_THEORECTICAL_);
	

	uint8_t width_  = ST77XX_COL_E_LOW_MAX_THEORECTICAL_ - ST77XX_COL_S_LOW_;
	uint8_t height_ = ST77XX_ROW_E_LOW_MAX_THEORECTICAL_ - ST77XX_ROW_S_LOW_;

	// TH: selects 18 bits per pixel -> 3-byte transfer for each pixel.
	uint32_t color_   = ST77XX_COLOR_0_;
	uint8_t  color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	uint8_t  color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	uint8_t  color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	
	
	// TH: sends write memory command.
	spi_write_seq_cmd_(ST77XX_RAMWR);
	
	// TH: sets D/C bit for data.
	PORTA  |= (1<<PORTA3);

	// TH: enables byte-shifting (i.e. pulls CS_BAR low).
	PORTB  &= (~(1<<PORTB4));

	for(uint16_t index=width_*height_/2; index>0; index--){

		// TH: starts SPI clock generator.
		SPDR0 = color_2_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

		// TH: starts SPI clock generator.
		SPDR0 = color_1_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

		// TH: starts SPI clock generator.
		SPDR0 = color_0_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

	}//for index.

	// TH: disables byte-shifting (i.e. pulls CS_BAR high).
	PORTB  |= (1<<PORTB4);

	color_   = ST77XX_COLOR_0_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;

	// TH: enables byte-shifting (i.e. pulls CS_BAR low).
	PORTB  &= (~(1<<PORTB4));

	for(uint16_t index=width_*height_/2; index>0; index--){

		// TH: starts SPI clock generator.
		SPDR0 = color_2_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

		// TH: starts SPI clock generator.
		SPDR0 = color_1_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

		// TH: starts SPI clock generator.
		SPDR0 = color_0_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

	}//for index.

	// TH: disables byte-shifting (i.e. pulls CS_BAR high).
	PORTB  |= (1<<PORTB4);

}//write_pattern_0_.

void write_char_(
uint8_t num_,
uint8_t col_s_high, uint8_t col_s_low, uint8_t col_e_high, uint8_t col_e_low, 
uint8_t row_s_high, uint8_t row_s_low, uint8_t row_e_high, uint8_t row_e_low
){
	
	// TH: slow mode.

	// TH: checks if column boundary already fixed by caller.
	if(col_e_low_>ST77XX_COL_E_LOW_MAX_PORTRAIT_){
		
		row_s_high_=ST77XX_ROW_S_HIGH_;
		row_s_low_ =row_e_low+2;
		row_e_high_=ST77XX_ROW_E_HIGH_;
		row_e_low_ =row_s_low_+6;

		col_s_high_=ST77XX_COL_S_HIGH_;
		col_s_low_ =ST77XX_COL_S_LOW_MIN_ ;
		col_e_high_=ST77XX_COL_E_HIGH_;
		col_e_low_ =col_s_low_+4;

	}
	
	spi_write_seq_window_(col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

	// TH: sends write memory command.
	spi_write_seq_cmd_(ST77XX_RAMWR);

	uint8_t mask; uint8_t data;
	for(uint8_t row=0; row<ST77XX_CHAR_SIZE_ROW_; row++){
		
		// TH: starts from left to right.
		mask = 0x10;

		// TH: reads a byte from the program space with a 16-bit (near) address.
		data = pgm_read_byte(&((*(FONT_CHAR+num_))[row]));

		for(uint8_t col=0; col<ST77XX_CHAR_SIZE_COL_; col++){
			
			// TH: selects 18 bits per pixel -> 3-byte transfer for each pixel.
			uint32_t color_;

			// TH: consults bitmap ...
			if((data & mask)==0x0)      color_   = ST77XX_COLOR_0_;
			else                        color_   = ST77XX_COLOR_1_;
			
			uint8_t  color_2_ = ((uint8_t)(color_>>16)) & 0x03;
			uint8_t  color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
			uint8_t  color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;

			// TH: sets D/C bit for data.
			PORTA  |= (1<<PORTA3);

			// TH: enables byte-shifting (i.e. pulls CS_BAR low).
			PORTB  &= (~(1<<PORTB4));

			// TH: starts SPI clock generator.
			SPDR0 = color_2_;

			// TH: waits for any previous transmission to complete.
			while ( !(SPSR0 & (1<<SPIF0)) );

			// TH: starts SPI clock generator.
			SPDR0 = color_1_;

			// TH: waits for any previous transmission to complete.
			while ( !(SPSR0 & (1<<SPIF0)) );

			// TH: starts SPI clock generator.
			SPDR0 = color_0_;

			// TH: waits for any previous transmission to complete.
			while ( !(SPSR0 & (1<<SPIF0)) );

			// TH: disables byte-shifting (i.e. pulls CS_BAR high).
			PORTB  |= (1<<PORTB4);

			// TH: shifts right for next column pixel.
			mask >>= 1;

		}//for col.

	}//for row.
	
	;

	
	/*
	// TH: fast mode --- demo: writes 'A' to display.
	
	spi_write_seq_window_(col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);

	// TH: sends write memory command.
	spi_write_seq_cmd_(ST77XX_RAMWR);

	uint32_t color_   = ST77XX_COLOR_0_;
	uint8_t color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	uint8_t color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	uint8_t color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)2,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_1_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)1,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_0_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)3,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_1_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)1,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_0_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)1,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_1_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)1,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_0_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)1,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_1_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)1,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_0_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)3,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_1_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)2,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_0_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)3,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_1_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)7,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_0_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)3,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_1_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)2,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_0_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)3,color_2_,color_1_,color_0_);

	color_   = ST77XX_COLOR_1_;
	color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	spi_write_seq_param_((uint32_t)1,color_2_,color_1_,color_0_);
	*/
	;

}//write_char_.

void spi_write_seq_param_(uint32_t iter_, uint8_t color_2_, uint8_t color_1_, uint8_t color_0_){
	
	// TH: sets D/C bit for data.
	PORTA  |= (1<<PORTA3);

	// TH: enables byte-shifting (i.e. pulls CS_BAR low).
	PORTB  &= (~(1<<PORTB4));
	
	for(uint32_t i=0; i<iter_; i++){
		
		// TH: starts SPI clock generator.
		SPDR0 = color_2_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

		// TH: starts SPI clock generator.
		SPDR0 = color_1_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

		// TH: starts SPI clock generator.
		SPDR0 = color_0_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

	}//for i.

	// TH: disables byte-shifting (i.e. pulls CS_BAR high).
	PORTB  |= (1<<PORTB4);

}//spi_write_seq_param_.

void spi_write_seq_window_(
uint8_t col_s_high_, uint8_t col_s_low_, uint8_t col_e_high_, uint8_t col_e_low_, 
uint8_t row_s_high_, uint8_t row_s_low_, uint8_t row_e_high_, uint8_t row_e_low_
){
	
	// TH: sets column window.
	spi_write_seq_cmd_(ST77XX_CASET);

	// TH: sends high byte and low byte for start column.
	spi_write_seq_data_(col_s_high_);
	spi_write_seq_data_(col_s_low_ );

	// TH: sends high byte and low byte for end column.
	spi_write_seq_data_(col_e_high_);
	spi_write_seq_data_(col_e_low_);

	// TH: sets row window.
	spi_write_seq_cmd_(ST77XX_RASET);

	// TH: sends high byte and low byte for start row.
	spi_write_seq_data_(row_s_high_);
	spi_write_seq_data_(row_s_low_);

	// TH: sends high byte and low byte for end row.
	spi_write_seq_data_(row_e_high_);
	spi_write_seq_data_(row_e_low_);

}//spi_write_seq_window_.

void write_row_portrait_
(
uint8_t index, 
uint8_t col_s_high, uint8_t col_s_low, uint8_t col_e_high, uint8_t col_e_low, 
uint8_t row_s_high, uint8_t row_s_low, uint8_t row_e_high, uint8_t row_e_low
){
	
	
	// TH: checks if column boundary already fixed by caller.
	if(col_e_low_>ST77XX_COL_E_LOW_MAX_PORTRAIT_){
		
		row_s_high_=ST77XX_ROW_S_HIGH_;
		row_s_low_ =row_e_low+2;
		row_e_high_=ST77XX_ROW_E_HIGH_;
		row_e_low_ =row_s_low_+6;

		col_s_high_=ST77XX_COL_S_HIGH_;
		col_s_low_ =ST77XX_COL_S_LOW_MIN_ ;
		col_e_high_=ST77XX_COL_E_HIGH_;
		col_e_low_ =col_s_low_+4;

	}
	

	for(uint8_t i=0; i<COL_MAX_7_BY_5_; i++){
		
		write_char_(index, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
		
		col_s_high_=ST77XX_COL_S_HIGH_;
		col_s_low_ =col_e_low_+2 ;
		col_e_high_=ST77XX_COL_E_HIGH_;
		col_e_low_ =col_s_low_+4;
		
	}//for i.

}//write_row_portrait_.

void write_row_text_(
char * ptr_str_,
uint8_t col_s_high, uint8_t col_s_low, uint8_t col_e_high, uint8_t col_e_low,
uint8_t row_s_high, uint8_t row_s_low, uint8_t row_e_high, uint8_t row_e_low
){
	
	uint8_t wrapped = 0;

	// TH: checks if row boundary already fixed by caller.
	if(row_e_low_>ST77XX_ROW_E_LOW_MAX_PORTRAIT_){
		
		row_s_high_=ST77XX_ROW_S_HIGH_;
		row_s_low_ =ST77XX_ROW_S_LOW_MIN_;
		row_e_high_=ST77XX_ROW_E_HIGH_;
		row_e_low_ =row_s_low_+6;
		
		col_s_high_=ST77XX_COL_S_HIGH_;
		col_s_low_ =ST77XX_COL_S_LOW_MIN_ ;
		col_e_high_=ST77XX_COL_E_HIGH_;
		col_e_low_ =col_s_low_+4;

		wrapped=1;

	}

	write_pattern_1_();

	for(uint8_t i=0; *(ptr_str_+i)!='\0'; i++){
		
		for(uint8_t i2=0; i2<NCHARS; i2++){
			
			if(*(ptr_str_+i)==tab_char_[i2].c_){
				
				write_char_(tab_char_[i2].i_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				col_s_high_=ST77XX_COL_S_HIGH_;
				col_s_low_ =col_e_low_+2 ;
				col_e_high_=ST77XX_COL_E_HIGH_;
				col_e_low_ =col_s_low_+4;
				break;

			}//if matched.

		}//for i2.
		
	}//for i.

	row_s_high_=ST77XX_ROW_S_HIGH_;
	
	if(wrapped==0) row_s_low_ =row_e_low +2; // TH: if NOT yet wrapped around.
	else           row_s_low_ =row_e_low_+2; // TH: if already wrapped around.

	row_e_high_=ST77XX_ROW_E_HIGH_;
	row_e_low_ =row_s_low_+6;
	
	col_s_high_=ST77XX_COL_S_HIGH_;
	col_s_low_ =ST77XX_COL_S_LOW_MIN_ ;
	col_e_high_=ST77XX_COL_E_HIGH_;
	col_e_low_ =col_s_low_+4;

}//write_row_text_.

void write_row_number_(
uint32_t number_,
uint8_t col_s_high, uint8_t col_s_low, uint8_t col_e_high, uint8_t col_e_low,
uint8_t row_s_high, uint8_t row_s_low, uint8_t row_e_high, uint8_t row_e_low
){
	
	uint8_t wrapped = 0;

	// TH: checks if row boundary already fixed by caller.
	if(row_e_low_>ST77XX_ROW_E_LOW_MAX_PORTRAIT_){
		
		row_s_high_=ST77XX_ROW_S_HIGH_;
		row_s_low_ =ST77XX_ROW_S_LOW_MIN_;
		row_e_high_=ST77XX_ROW_E_HIGH_;
		row_e_low_ =row_s_low_+6;
		
		col_s_high_=ST77XX_COL_S_HIGH_;
		col_s_low_ =ST77XX_COL_S_LOW_MIN_ ;
		col_e_high_=ST77XX_COL_E_HIGH_;
		col_e_low_ =col_s_low_+4;

		wrapped=1;

	}
	
	write_pattern_1_();

	for(uint8_t i=sizeof(uint32_t)-1; i>=0; i--){
		
		// TH: retrieves each byte, MSByte first.
		uint8_t byte_ = (uint8_t)(number_>>((i)*8));

		// TH: retrieves the nibbles.
		uint8_t upper_ = (byte_ >> 4) & 0xF;
		for(uint8_t i2=0; i2<NNUMS; i2++){
			if(upper_==tab_num_[i2].n_){
				write_char_(tab_num_[i2].i_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				col_s_high_=ST77XX_COL_S_HIGH_;
				col_s_low_ =col_e_low_+2 ;
				col_e_high_=ST77XX_COL_E_HIGH_;
				col_e_low_ =col_s_low_+4;
				break;
			}//if matched.
		}//for i2.
		
		uint8_t lower_ = (byte_ >> 0) & 0xF;
		for(uint8_t i2=0; i2<NNUMS; i2++){
			if(lower_==tab_num_[i2].n_){
				write_char_(tab_num_[i2].i_, col_s_high_, col_s_low_, col_e_high_, col_e_low_, row_s_high_, row_s_low_, row_e_high_, row_e_low_);
				col_s_high_=ST77XX_COL_S_HIGH_;
				col_s_low_ =col_e_low_+2 ;
				col_e_high_=ST77XX_COL_E_HIGH_;
				col_e_low_ =col_s_low_+4;
				break;
			}//if matched.
		}//for i2.

		if(i==0) {
			
			row_s_high_=ST77XX_ROW_S_HIGH_;
			
			if(wrapped==0) row_s_low_ =row_e_low +2; // TH: if NOT yet wrapped around.
			else           row_s_low_ =row_e_low_+2; // TH: if already wrapped around.

			row_e_high_=ST77XX_ROW_E_HIGH_;
			row_e_low_ =row_s_low_+6;

			col_s_high_=ST77XX_COL_S_HIGH_;
			col_s_low_ =ST77XX_COL_S_LOW_MIN_ ;
			col_e_high_=ST77XX_COL_E_HIGH_;
			col_e_low_ =col_s_low_+4;

			return;

		}//if 0.

	}//for i.
	

	;

}//write_row_number_.

void write_pattern_1_(void){
	
	// TH: sets column window.
	spi_write_seq_cmd_(ST77XX_CASET);

	// TH: sends high byte and low byte for start column.
	spi_write_seq_data_(ST77XX_COL_S_HIGH_);
	spi_write_seq_data_(ST77XX_COL_S_LOW_);

	// TH: sends high byte and low byte for end column.
	spi_write_seq_data_(ST77XX_COL_E_HIGH_);
	spi_write_seq_data_(ST77XX_COL_E_LOW_MAX_THEORECTICAL_);

	// TH: sets row window.
	spi_write_seq_cmd_(ST77XX_RASET);

	// TH: sends high byte and low byte for start row.
	spi_write_seq_data_(ST77XX_ROW_S_HIGH_);
	spi_write_seq_data_(row_s_low_ );

	// TH: sends high byte and low byte for end row.
	spi_write_seq_data_(ST77XX_ROW_E_HIGH_);
	spi_write_seq_data_(row_e_low_);
	

	uint8_t width_  = ST77XX_COL_E_LOW_MAX_THEORECTICAL_ - ST77XX_COL_S_LOW_;
	uint8_t height_ = row_e_low_ - row_s_low_ + 1;

	// TH: selects 18 bits per pixel -> 3-byte transfer for each pixel.
	uint32_t color_   = ST77XX_COLOR_0_;
	uint8_t  color_2_ = ((uint8_t)(color_>>16)) & 0x03;
	uint8_t  color_1_ = ((uint8_t)(color_>> 8)) & 0xFF;
	uint8_t  color_0_ = ((uint8_t)(color_>> 0)) & 0xFF;
	
	
	// TH: sends write memory command.
	spi_write_seq_cmd_(ST77XX_RAMWR);
	
	// TH: sets D/C bit for data.
	PORTA  |= (1<<PORTA3);

	// TH: enables byte-shifting (i.e. pulls CS_BAR low).
	PORTB  &= (~(1<<PORTB4));

	for(uint16_t index=width_*height_; index>0; index--){

		// TH: starts SPI clock generator.
		SPDR0 = color_2_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

		// TH: starts SPI clock generator.
		SPDR0 = color_1_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

		// TH: starts SPI clock generator.
		SPDR0 = color_0_;

		// TH: waits for any previous transmission to complete.
		while ( !(SPSR0 & (1<<SPIF0)) );

	}//for index.

	// TH: disables byte-shifting (i.e. pulls CS_BAR high).
	PORTB  |= (1<<PORTB4);

}//write_pattern_1_.
/*
ISR(PCINT0_vect){
	
	// TH: latches ONLY 1st toggle.
	// TH: interrupt capture versus 'flash' :)
	dip_changed_ = 1;

}//PCINT0_vect.
*/
void as7262_write_virtual_(uint8_t virtual_,uint8_t d_){
	
	volatile uint8_t status_;

	while (1){
		
		// TH: reads slave I²C status to see if the read buffer is ready.
		status_ = i2cm_read(I2C_AS72XX_SLAVE_ADDR_REG_STATUS_);

		if ((status_ & (1<<I2C_AS72XX_SLAVE_STATUS_TX_VALID_)) == 0) break;
		_delay_us(1);

	}//while 1.

	// TH: issues pending write request on given virtual register.
	i2cm_write(I2C_AS72XX_SLAVE_ADDR_REG_WRITE_, virtual_|0x80);

	while (1){
		
		// TH: reads slave I²C status to see if the read buffer is ready.
		status_ = i2cm_read(I2C_AS72XX_SLAVE_ADDR_REG_STATUS_);

		if ((status_ & (1<<I2C_AS72XX_SLAVE_STATUS_TX_VALID_)) == 0) break;
		_delay_us(1);

	}//while 1.

	i2cm_write(I2C_AS72XX_SLAVE_ADDR_REG_WRITE_, d_);

}//as7262_write_virtual_.

void timer1_OC1A_disabled_high_(){
	
	// TH: initially Timer is STOPPED.
	TCCR1B &= (~(1<<CS12)) & (~(1<<CS11)) & (~(1<<CS10));

	// TH: disables OC1A for now.
	TCCR1A &=   (~((1<<COM1A1)))  &    (~((1<<COM1A0)));
	
	// TH: sets Port D: Pin X as output.
	DDRD   |=   (1<<DDD5);
	PORTD  |=   (1<<PORTD5) ;

}//timer1_OC1A_disabled_high_.

void timer1_OC1A_disabled_low_(){
	
	// TH: initially Timer is STOPPED.
	TCCR1B &= (~(1<<CS12)) & (~(1<<CS11)) & (~(1<<CS10));

	// TH: disables OC1A for now.
	TCCR1A &=   (~((1<<COM1A1)))  &    (~((1<<COM1A0)));
	
	// TH: sets Port D: Pin X as output.
	DDRD   |=      (1<<DDD5);
	PORTD  &=   (~((1<<PORTD5))) ;

}//timer1_OC1A_disabled_low_.

;
