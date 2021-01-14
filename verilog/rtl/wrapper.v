`default_nettype none
module wrapper (
    // interface as user_proj_example.v
    input wb_clk_i,
    input wb_rst_i,
    input wbs_stb_i,
    input wbs_cyc_i,
    input wbs_we_i,
    input [3:0] wbs_sel_i,
    input [31:0] wbs_dat_i,
    input [31:0] wbs_adr_i,
    output wbs_ack_o,
    output [31:0] wbs_dat_o,

    // Logic Analyzer Signals
    // only provide first 32 bits to reduce wiring congestion
    input  [31:0] la_data_in,
    output [31:0] la_data_out,
    input  [31:0] la_oen,

    // IOs
    input  [`MPRJ_IO_PADS-1:0] io_in,
    output [`MPRJ_IO_PADS-1:0] io_out,
    output [`MPRJ_IO_PADS-1:0] io_oeb,
    
    // active input, only connect tristated outputs if this is high
    input active
);

    // all outputs must be tristated before being passed onto the project
    wire buf_wbs_ack_o;
    wire [31:0] buf_wbs_dat_o;
    wire [31:0] buf_la_data_out;
    wire [`MPRJ_IO_PADS-1:0] buf_io_out;
    wire [`MPRJ_IO_PADS-1:0] buf_io_oeb;

    // tristate buffers
    wire active_n = ! active; // TODO reverse order below if this works
    assign wbs_ack_o    = active_n ? 1'bz              : buf_wbs_ack_o;
    assign wbs_dat_o    = active_n ? 32'bz             : buf_wbs_dat_o;
    assign la_data_out  = active_n ? 32'bz             : buf_la_data_out;
    assign io_out       = active_n ? `MPRJ_IO_PADS'bz  : buf_io_out;
    assign io_oeb       = active_n ? `MPRJ_IO_PADS'bz  : buf_io_oeb;

    // permanently set oeb so that outputs are always enabled: 0 is output, 1 is high-impedance
    assign buf_io_oeb = `MPRJ_IO_PADS'h0;
    // instantiate your module here, connecting what you need of the above signals
    seven_segment_seconds seven_segment_seconds (.clk(wb_clk_i), .reset(la_data_in[25]), .led_out(buf_io_out[14:8]), .compare_in(la_data_in[23:0]), .update_compare(la_data_in[24]));

endmodule 
`default_nettype wire
