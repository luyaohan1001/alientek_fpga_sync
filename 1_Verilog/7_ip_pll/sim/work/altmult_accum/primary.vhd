library verilog;
use verilog.vl_types.all;
entity altmult_accum is
    generic(
        width_a         : integer := 2;
        width_b         : integer := 2;
        width_c         : integer := 22;
        width_result    : integer := 5;
        number_of_multipliers: integer := 1;
        input_reg_a     : string  := "CLOCK0";
        input_aclr_a    : string  := "ACLR3";
        multiplier1_direction: string  := "UNUSED";
        multiplier3_direction: string  := "UNUSED";
        input_reg_b     : string  := "CLOCK0";
        input_aclr_b    : string  := "ACLR3";
        port_addnsub    : string  := "PORT_CONNECTIVITY";
        addnsub_reg     : string  := "CLOCK0";
        addnsub_aclr    : string  := "ACLR3";
        addnsub_pipeline_reg: string  := "CLOCK0";
        addnsub_pipeline_aclr: string  := "ACLR3";
        accum_direction : string  := "ADD";
        accum_sload_reg : string  := "CLOCK0";
        accum_sload_aclr: string  := "ACLR3";
        accum_sload_pipeline_reg: string  := "CLOCK0";
        accum_sload_pipeline_aclr: string  := "ACLR3";
        representation_a: string  := "UNSIGNED";
        port_signa      : string  := "PORT_CONNECTIVITY";
        sign_reg_a      : string  := "CLOCK0";
        sign_aclr_a     : string  := "ACLR3";
        sign_pipeline_reg_a: string  := "CLOCK0";
        sign_pipeline_aclr_a: string  := "ACLR3";
        port_signb      : string  := "PORT_CONNECTIVITY";
        representation_b: string  := "UNSIGNED";
        sign_reg_b      : string  := "CLOCK0";
        sign_aclr_b     : string  := "ACLR3";
        sign_pipeline_reg_b: string  := "CLOCK0";
        sign_pipeline_aclr_b: string  := "ACLR3";
        multiplier_reg  : string  := "CLOCK0";
        multiplier_aclr : string  := "ACLR3";
        output_reg      : string  := "CLOCK0";
        output_aclr     : string  := "ACLR3";
        lpm_type        : string  := "altmult_accum";
        lpm_hint        : string  := "UNUSED";
        extra_multiplier_latency: integer := 0;
        extra_accumulator_latency: integer := 0;
        dedicated_multiplier_circuitry: string  := "AUTO";
        dsp_block_balancing: string  := "AUTO";
        intended_device_family: string  := "Stratix";
        accum_round_aclr: string  := "ACLR3";
        accum_round_pipeline_aclr: string  := "ACLR3";
        accum_round_pipeline_reg: string  := "CLOCK0";
        accum_round_reg : string  := "CLOCK0";
        accum_saturation_aclr: string  := "ACLR3";
        accum_saturation_pipeline_aclr: string  := "ACLR3";
        accum_saturation_pipeline_reg: string  := "CLOCK0";
        accum_saturation_reg: string  := "CLOCK0";
        accum_sload_upper_data_aclr: string  := "ACLR3";
        accum_sload_upper_data_pipeline_aclr: string  := "ACLR3";
        accum_sload_upper_data_pipeline_reg: string  := "CLOCK0";
        accum_sload_upper_data_reg: string  := "CLOCK0";
        mult_round_aclr : string  := "ACLR3";
        mult_round_reg  : string  := "CLOCK0";
        mult_saturation_aclr: string  := "ACLR3";
        mult_saturation_reg: string  := "CLOCK0";
        input_source_a  : string  := "DATAA";
        input_source_b  : string  := "DATAB";
        width_upper_data: integer := 1;
        multiplier_rounding: string  := "NO";
        multiplier_saturation: string  := "NO";
        accumulator_rounding: string  := "NO";
        accumulator_saturation: string  := "NO";
        port_mult_is_saturated: string  := "UNUSED";
        port_accum_is_saturated: string  := "UNUSED";
        int_width_a     : vl_notype;
        int_width_b     : vl_notype;
        int_width_result: vl_notype;
        int_extra_width : vl_notype;
        diff_width_a    : vl_notype;
        diff_width_b    : vl_notype;
        sat_for_ini     : vl_notype;
        mult_round_for_ini: vl_notype;
        bits_to_round   : vl_notype;
        sload_for_limit : vl_notype;
        accum_sat_for_limit: vl_notype;
        int_width_extra_bit: vl_notype;
        preadder_mode   : string  := "SIMPLE";
        loadconst_value : integer := 0;
        width_coef      : integer := 0;
        loadconst_control_register: string  := "CLOCK0";
        loadconst_control_aclr: string  := "ACLR0";
        coefsel0_register: string  := "CLOCK0";
        coefsel1_register: string  := "CLOCK0";
        coefsel2_register: string  := "CLOCK0";
        coefsel3_register: string  := "CLOCK0";
        coefsel0_aclr   : string  := "ACLR0";
        coefsel1_aclr   : string  := "ACLR0";
        coefsel2_aclr   : string  := "ACLR0";
        coefsel3_aclr   : string  := "ACLR0";
        preadder_direction_0: string  := "ADD";
        preadder_direction_1: string  := "ADD";
        preadder_direction_2: string  := "ADD";
        preadder_direction_3: string  := "ADD";
        systolic_delay1 : string  := "UNREGISTERED";
        systolic_delay3 : string  := "UNREGISTERED";
        systolic_aclr1  : string  := "NONE";
        systolic_aclr3  : string  := "NONE";
        coef0_0         : integer := 0;
        coef0_1         : integer := 0;
        coef0_2         : integer := 0;
        coef0_3         : integer := 0;
        coef0_4         : integer := 0;
        coef0_5         : integer := 0;
        coef0_6         : integer := 0;
        coef0_7         : integer := 0;
        coef1_0         : integer := 0;
        coef1_1         : integer := 0;
        coef1_2         : integer := 0;
        coef1_3         : integer := 0;
        coef1_4         : integer := 0;
        coef1_5         : integer := 0;
        coef1_6         : integer := 0;
        coef1_7         : integer := 0;
        coef2_0         : integer := 0;
        coef2_1         : integer := 0;
        coef2_2         : integer := 0;
        coef2_3         : integer := 0;
        coef2_4         : integer := 0;
        coef2_5         : integer := 0;
        coef2_6         : integer := 0;
        coef2_7         : integer := 0;
        coef3_0         : integer := 0;
        coef3_1         : integer := 0;
        coef3_2         : integer := 0;
        coef3_3         : integer := 0;
        coef3_4         : integer := 0;
        coef3_5         : integer := 0;
        coef3_6         : integer := 0;
        coef3_7         : integer := 0
    );
    port(
        dataa           : in     vl_logic_vector;
        datab           : in     vl_logic_vector;
        datac           : in     vl_logic_vector;
        scanina         : in     vl_logic_vector;
        scaninb         : in     vl_logic_vector;
        sourcea         : in     vl_logic;
        sourceb         : in     vl_logic;
        accum_sload_upper_data: in     vl_logic_vector;
        addnsub         : in     vl_logic;
        accum_sload     : in     vl_logic;
        signa           : in     vl_logic;
        signb           : in     vl_logic;
        clock0          : in     vl_logic;
        clock1          : in     vl_logic;
        clock2          : in     vl_logic;
        clock3          : in     vl_logic;
        ena0            : in     vl_logic;
        ena1            : in     vl_logic;
        ena2            : in     vl_logic;
        ena3            : in     vl_logic;
        aclr0           : in     vl_logic;
        aclr1           : in     vl_logic;
        aclr2           : in     vl_logic;
        aclr3           : in     vl_logic;
        result          : out    vl_logic_vector;
        overflow        : out    vl_logic;
        scanouta        : out    vl_logic_vector;
        scanoutb        : out    vl_logic_vector;
        mult_round      : in     vl_logic;
        mult_saturation : in     vl_logic;
        accum_round     : in     vl_logic;
        accum_saturation: in     vl_logic;
        mult_is_saturated: out    vl_logic;
        accum_is_saturated: out    vl_logic;
        coefsel0        : in     vl_logic_vector(2 downto 0);
        coefsel1        : in     vl_logic_vector(2 downto 0);
        coefsel2        : in     vl_logic_vector(2 downto 0);
        coefsel3        : in     vl_logic_vector(2 downto 0)
    );
    attribute mti_svvh_generic_type : integer;
    attribute mti_svvh_generic_type of width_a : constant is 1;
    attribute mti_svvh_generic_type of width_b : constant is 1;
    attribute mti_svvh_generic_type of width_c : constant is 1;
    attribute mti_svvh_generic_type of width_result : constant is 1;
    attribute mti_svvh_generic_type of number_of_multipliers : constant is 1;
    attribute mti_svvh_generic_type of input_reg_a : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_a : constant is 1;
    attribute mti_svvh_generic_type of multiplier1_direction : constant is 1;
    attribute mti_svvh_generic_type of multiplier3_direction : constant is 1;
    attribute mti_svvh_generic_type of input_reg_b : constant is 1;
    attribute mti_svvh_generic_type of input_aclr_b : constant is 1;
    attribute mti_svvh_generic_type of port_addnsub : constant is 1;
    attribute mti_svvh_generic_type of addnsub_reg : constant is 1;
    attribute mti_svvh_generic_type of addnsub_aclr : constant is 1;
    attribute mti_svvh_generic_type of addnsub_pipeline_reg : constant is 1;
    attribute mti_svvh_generic_type of addnsub_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_direction : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_reg : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_pipeline_reg : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of representation_a : constant is 1;
    attribute mti_svvh_generic_type of port_signa : constant is 1;
    attribute mti_svvh_generic_type of sign_reg_a : constant is 1;
    attribute mti_svvh_generic_type of sign_aclr_a : constant is 1;
    attribute mti_svvh_generic_type of sign_pipeline_reg_a : constant is 1;
    attribute mti_svvh_generic_type of sign_pipeline_aclr_a : constant is 1;
    attribute mti_svvh_generic_type of port_signb : constant is 1;
    attribute mti_svvh_generic_type of representation_b : constant is 1;
    attribute mti_svvh_generic_type of sign_reg_b : constant is 1;
    attribute mti_svvh_generic_type of sign_aclr_b : constant is 1;
    attribute mti_svvh_generic_type of sign_pipeline_reg_b : constant is 1;
    attribute mti_svvh_generic_type of sign_pipeline_aclr_b : constant is 1;
    attribute mti_svvh_generic_type of multiplier_reg : constant is 1;
    attribute mti_svvh_generic_type of multiplier_aclr : constant is 1;
    attribute mti_svvh_generic_type of output_reg : constant is 1;
    attribute mti_svvh_generic_type of output_aclr : constant is 1;
    attribute mti_svvh_generic_type of lpm_type : constant is 1;
    attribute mti_svvh_generic_type of lpm_hint : constant is 1;
    attribute mti_svvh_generic_type of extra_multiplier_latency : constant is 1;
    attribute mti_svvh_generic_type of extra_accumulator_latency : constant is 1;
    attribute mti_svvh_generic_type of dedicated_multiplier_circuitry : constant is 1;
    attribute mti_svvh_generic_type of dsp_block_balancing : constant is 1;
    attribute mti_svvh_generic_type of intended_device_family : constant is 1;
    attribute mti_svvh_generic_type of accum_round_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_round_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_round_pipeline_reg : constant is 1;
    attribute mti_svvh_generic_type of accum_round_reg : constant is 1;
    attribute mti_svvh_generic_type of accum_saturation_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_saturation_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_saturation_pipeline_reg : constant is 1;
    attribute mti_svvh_generic_type of accum_saturation_reg : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_upper_data_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_upper_data_pipeline_aclr : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_upper_data_pipeline_reg : constant is 1;
    attribute mti_svvh_generic_type of accum_sload_upper_data_reg : constant is 1;
    attribute mti_svvh_generic_type of mult_round_aclr : constant is 1;
    attribute mti_svvh_generic_type of mult_round_reg : constant is 1;
    attribute mti_svvh_generic_type of mult_saturation_aclr : constant is 1;
    attribute mti_svvh_generic_type of mult_saturation_reg : constant is 1;
    attribute mti_svvh_generic_type of input_source_a : constant is 1;
    attribute mti_svvh_generic_type of input_source_b : constant is 1;
    attribute mti_svvh_generic_type of width_upper_data : constant is 1;
    attribute mti_svvh_generic_type of multiplier_rounding : constant is 1;
    attribute mti_svvh_generic_type of multiplier_saturation : constant is 1;
    attribute mti_svvh_generic_type of accumulator_rounding : constant is 1;
    attribute mti_svvh_generic_type of accumulator_saturation : constant is 1;
    attribute mti_svvh_generic_type of port_mult_is_saturated : constant is 1;
    attribute mti_svvh_generic_type of port_accum_is_saturated : constant is 1;
    attribute mti_svvh_generic_type of int_width_a : constant is 3;
    attribute mti_svvh_generic_type of int_width_b : constant is 3;
    attribute mti_svvh_generic_type of int_width_result : constant is 3;
    attribute mti_svvh_generic_type of int_extra_width : constant is 3;
    attribute mti_svvh_generic_type of diff_width_a : constant is 3;
    attribute mti_svvh_generic_type of diff_width_b : constant is 3;
    attribute mti_svvh_generic_type of sat_for_ini : constant is 3;
    attribute mti_svvh_generic_type of mult_round_for_ini : constant is 3;
    attribute mti_svvh_generic_type of bits_to_round : constant is 3;
    attribute mti_svvh_generic_type of sload_for_limit : constant is 3;
    attribute mti_svvh_generic_type of accum_sat_for_limit : constant is 3;
    attribute mti_svvh_generic_type of int_width_extra_bit : constant is 3;
    attribute mti_svvh_generic_type of preadder_mode : constant is 1;
    attribute mti_svvh_generic_type of loadconst_value : constant is 1;
    attribute mti_svvh_generic_type of width_coef : constant is 1;
    attribute mti_svvh_generic_type of loadconst_control_register : constant is 1;
    attribute mti_svvh_generic_type of loadconst_control_aclr : constant is 1;
    attribute mti_svvh_generic_type of coefsel0_register : constant is 1;
    attribute mti_svvh_generic_type of coefsel1_register : constant is 1;
    attribute mti_svvh_generic_type of coefsel2_register : constant is 1;
    attribute mti_svvh_generic_type of coefsel3_register : constant is 1;
    attribute mti_svvh_generic_type of coefsel0_aclr : constant is 1;
    attribute mti_svvh_generic_type of coefsel1_aclr : constant is 1;
    attribute mti_svvh_generic_type of coefsel2_aclr : constant is 1;
    attribute mti_svvh_generic_type of coefsel3_aclr : constant is 1;
    attribute mti_svvh_generic_type of preadder_direction_0 : constant is 1;
    attribute mti_svvh_generic_type of preadder_direction_1 : constant is 1;
    attribute mti_svvh_generic_type of preadder_direction_2 : constant is 1;
    attribute mti_svvh_generic_type of preadder_direction_3 : constant is 1;
    attribute mti_svvh_generic_type of systolic_delay1 : constant is 1;
    attribute mti_svvh_generic_type of systolic_delay3 : constant is 1;
    attribute mti_svvh_generic_type of systolic_aclr1 : constant is 1;
    attribute mti_svvh_generic_type of systolic_aclr3 : constant is 1;
    attribute mti_svvh_generic_type of coef0_0 : constant is 1;
    attribute mti_svvh_generic_type of coef0_1 : constant is 1;
    attribute mti_svvh_generic_type of coef0_2 : constant is 1;
    attribute mti_svvh_generic_type of coef0_3 : constant is 1;
    attribute mti_svvh_generic_type of coef0_4 : constant is 1;
    attribute mti_svvh_generic_type of coef0_5 : constant is 1;
    attribute mti_svvh_generic_type of coef0_6 : constant is 1;
    attribute mti_svvh_generic_type of coef0_7 : constant is 1;
    attribute mti_svvh_generic_type of coef1_0 : constant is 1;
    attribute mti_svvh_generic_type of coef1_1 : constant is 1;
    attribute mti_svvh_generic_type of coef1_2 : constant is 1;
    attribute mti_svvh_generic_type of coef1_3 : constant is 1;
    attribute mti_svvh_generic_type of coef1_4 : constant is 1;
    attribute mti_svvh_generic_type of coef1_5 : constant is 1;
    attribute mti_svvh_generic_type of coef1_6 : constant is 1;
    attribute mti_svvh_generic_type of coef1_7 : constant is 1;
    attribute mti_svvh_generic_type of coef2_0 : constant is 1;
    attribute mti_svvh_generic_type of coef2_1 : constant is 1;
    attribute mti_svvh_generic_type of coef2_2 : constant is 1;
    attribute mti_svvh_generic_type of coef2_3 : constant is 1;
    attribute mti_svvh_generic_type of coef2_4 : constant is 1;
    attribute mti_svvh_generic_type of coef2_5 : constant is 1;
    attribute mti_svvh_generic_type of coef2_6 : constant is 1;
    attribute mti_svvh_generic_type of coef2_7 : constant is 1;
    attribute mti_svvh_generic_type of coef3_0 : constant is 1;
    attribute mti_svvh_generic_type of coef3_1 : constant is 1;
    attribute mti_svvh_generic_type of coef3_2 : constant is 1;
    attribute mti_svvh_generic_type of coef3_3 : constant is 1;
    attribute mti_svvh_generic_type of coef3_4 : constant is 1;
    attribute mti_svvh_generic_type of coef3_5 : constant is 1;
    attribute mti_svvh_generic_type of coef3_6 : constant is 1;
    attribute mti_svvh_generic_type of coef3_7 : constant is 1;
end altmult_accum;