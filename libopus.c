#if defined(__aarch64__) || defined(_M_ARM64)
#define ARCH_AARCH64
#elif defined(__arm__) || defined(_M_ARM)
#define ARCH_ARM
#elif defined(__x86_64__) || defined(_M_X64)
#define ARCH_X86_64
#elif defined(__i386__) || defined(_M_IX86)
#define ARCH_X86
#endif

#if defined(__aarch64__) || defined(_M_ARM64) || defined(__arm__) || defined(_M_ARM)
#define HAVE_ARM 1
#else
#define HAVE_ARM 0
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
#define HAVE_X86 1
#else
#define HAVE_X86 0
#endif


#ifdef _MSC_VER
#pragma warning(disable: 4244) // conversion from 'int' to 'opus_int16', possible loss of data
#endif

#define PACKAGE_VERSION "1.2.1-55-g840ccc94"
#define USE_ALLOCA            1

/* Comment out the next line for floating-point code */
// #define FIXED_POINT        1

#define OPUS_BUILD            1

#if HAVE_X86
/* Can always compile SSE intrinsics (no special compiler flags necessary) */
#define OPUS_X86_MAY_HAVE_SSE
#define OPUS_X86_MAY_HAVE_SSE2
#define OPUS_X86_MAY_HAVE_SSE4_1

/* Presume SSE functions, if compiled to use SSE/SSE2/AVX (note that AMD64 implies SSE2, and AVX implies SSE4.1) */
#define OPUS_X86_PRESUME_SSE 1
#define OPUS_X86_PRESUME_SSE2 1
//#if defined(__AVX__)
//#define OPUS_X86_PRESUME_SSE4_1 1
//#endif

#if !defined(OPUS_X86_PRESUME_SSE4_1) || !defined(OPUS_X86_PRESUME_SSE2) || !defined(OPUS_X86_PRESUME_SSE)
#define OPUS_HAVE_RTCD 1
#endif

#endif /* HAVE_X86 */


#define CELT_DECODER_C
#define CELT_ENCODER_C
#define ANALYSIS_C


#ifdef COMPILE_SSE41_ONLY

#if HAVE_X86
#if !defined(__SSE4_1__) && !defined(__AVX__)
#error libopus_sse4_1.c has to be compiled with sse4.1 enabled
#endif
#include "../silk/x86/NSQ_sse4_1.c"
#define NSQ_del_dec_struct NSQ_del_dec_struct_NSQ_del_dec_sse4_1
#define NSQ_sample_struct NSQ_sample_struct_NSQ_del_dec_sse4_1
#define NSQ_sample_pair NSQ_sample_pair_NSQ_del_dec_sse4_1
#include "../silk/x86/NSQ_del_dec_sse4_1.c"
#define tiltWeights tiltWeights_VAD_sse4_1
#include "../silk/x86/VAD_sse4_1.c"
#include "../silk/x86/VQ_WMat_EC_sse4_1.c"

#ifdef FIXED_POINT
#include "../silk/fixed/x86/vector_ops_FIX_sse4_1.c"
#include "../silk/fixed/x86/burg_modified_FIX_sse4_1.c"
#endif

#undef PI

// CELT:

#include "../celt/x86/celt_lpc_sse4_1.c"
#include "../celt/x86/pitch_sse4_1.c"
#endif /* HAVE_X86 */

#else

// SILK:

#include "../silk/CNG.c"
#include "../silk/code_signs.c"
#include "../silk/init_decoder.c"
#include "../silk/decode_core.c"
#include "../silk/decode_frame.c"
#include "../silk/decode_parameters.c"
#include "../silk/decode_indices.c"
#include "../silk/decode_pulses.c"
#include "../silk/decoder_set_fs.c"
#include "../silk/dec_API.c"
#include "../silk/enc_API.c"
#include "../silk/encode_indices.c"
#include "../silk/encode_pulses.c"
#include "../silk/gain_quant.c"
#include "../silk/interpolate.c"
#include "../silk/LP_variable_cutoff.c"
#include "../silk/NLSF_decode.c"
#include "../silk/NSQ.c"
#include "../silk/NSQ_del_dec.c"
#include "../silk/PLC.c"
#include "../silk/shell_coder.c"
#include "../silk/tables_gain.c"
#include "../silk/tables_LTP.c"
#include "../silk/tables_NLSF_CB_NB_MB.c"
#include "../silk/tables_NLSF_CB_WB.c"
#include "../silk/tables_other.c"
#include "../silk/tables_pitch_lag.c"
#include "../silk/tables_pulses_per_block.c"
#include "../silk/VAD.c"
#include "../silk/control_audio_bandwidth.c"
#include "../silk/quant_LTP_gains.c"
#include "../silk/VQ_WMat_EC.c"
#include "../silk/HP_variable_cutoff.c"
#include "../silk/NLSF_encode.c"
#include "../silk/NLSF_VQ.c"
#include "../silk/NLSF_unpack.c"
#include "../silk/NLSF_del_dec_quant.c"
#include "../silk/process_NLSFs.c"
#include "../silk/stereo_LR_to_MS.c"
#include "../silk/stereo_MS_to_LR.c"
#include "../silk/check_control_input.c"
#include "../silk/control_SNR.c"
#include "../silk/init_encoder.c"
#include "../silk/control_codec.c"
#include "../silk/A2NLSF.c"
#include "../silk/ana_filt_bank_1.c"
#include "../silk/biquad_alt.c"
#include "../silk/bwexpander_32.c"
#include "../silk/bwexpander.c"
#include "../silk/debug.c"
#include "../silk/decode_pitch.c"
#include "../silk/inner_prod_aligned.c"
#include "../silk/lin2log.c"
#include "../silk/log2lin.c"
#include "../silk/LPC_analysis_filter.c"
#include "../silk/LPC_inv_pred_gain.c"
#undef QA
#include "../silk/table_LSF_cos.c"
#include "../silk/NLSF2A.c"
#undef QA
#include "../silk/NLSF_stabilize.c"
#include "../silk/NLSF_VQ_weights_laroia.c"
#include "../silk/pitch_est_tables.c"
#include "../silk/resampler.c"
#include "../silk/resampler_down2_3.c"
#include "../silk/resampler_down2.c"
#include "../silk/resampler_private_AR2.c"
#include "../silk/resampler_private_down_FIR.c"
#include "../silk/resampler_private_IIR_FIR.c"
#include "../silk/resampler_private_up2_HQ.c"
#include "../silk/resampler_rom.c"
#include "../silk/sigm_Q15.c"
#include "../silk/sort.c"
#include "../silk/sum_sqr_shift.c"
#include "../silk/stereo_decode_pred.c"
#include "../silk/stereo_encode_pred.c"
#include "../silk/stereo_find_predictor.c"
#include "../silk/stereo_quant_pred.c"
#include "../silk/LPC_fit.c"

#if HAVE_X86
#include "../silk/x86/x86_silk_map.c"
#endif

#if HAVE_ARM
#ifdef FIXED_POINT
#include "../silk/arm/arm_silk_map.c"
#include "../silk/arm/biquad_alt_neon_intr.c"
#endif
#include "../silk/arm/LPC_inv_pred_gain_neon_intr.c"
#undef QA
#include "../silk/arm/NSQ_del_dec_neon_intr.c"
#include "../silk/arm/NSQ_neon.c"
#endif

#ifdef FIXED_POINT
#include "../silk/fixed/LTP_analysis_filter_FIX.c"
#include "../silk/fixed/LTP_scale_ctrl_FIX.c"
#include "../silk/fixed/corrMatrix_FIX.c"
#include "../silk/fixed/encode_frame_FIX.c"
#include "../silk/fixed/find_LPC_FIX.c"
#include "../silk/fixed/find_LTP_FIX.c"
#include "../silk/fixed/find_pitch_lags_FIX.c"
#include "../silk/fixed/find_pred_coefs_FIX.c"
#include "../silk/fixed/noise_shape_analysis_FIX.c"
#include "../silk/fixed/process_gains_FIX.c"
#include "../silk/fixed/regularize_correlations_FIX.c"
#include "../silk/fixed/residual_energy16_FIX.c"
#include "../silk/fixed/residual_energy_FIX.c"
#include "../silk/fixed/warped_autocorrelation_FIX.c"
#include "../silk/fixed/apply_sine_window_FIX.c"
#include "../silk/fixed/autocorr_FIX.c"
#undef QA
#include "../silk/fixed/burg_modified_FIX.c"
#undef QA
#undef N_BITS_HEAD_ROOM
#include "../silk/fixed/k2a_FIX.c"
#include "../silk/fixed/k2a_Q16_FIX.c"
#include "../silk/fixed/pitch_analysis_core_FIX.c"
#include "../silk/fixed/vector_ops_FIX.c"
#include "../silk/fixed/schur64_FIX.c"
#include "../silk/fixed/schur_FIX.c"

#if HAVE_ARM
#include "../silk/fixed/arm/warped_autocorrelation_FIX_neon_intr.c"
#endif
#endif

#ifndef FIXED_POINT
#include "../silk/float/apply_sine_window_FLP.c"
#include "../silk/float/corrMatrix_FLP.c"
#include "../silk/float/encode_frame_FLP.c"
#include "../silk/float/find_LPC_FLP.c"
#include "../silk/float/find_LTP_FLP.c"
#include "../silk/float/find_pitch_lags_FLP.c"
#include "../silk/float/find_pred_coefs_FLP.c"
#include "../silk/float/LPC_analysis_filter_FLP.c"
#include "../silk/float/LTP_analysis_filter_FLP.c"
#include "../silk/float/LTP_scale_ctrl_FLP.c"
#include "../silk/float/noise_shape_analysis_FLP.c"
#include "../silk/float/process_gains_FLP.c"
#include "../silk/float/regularize_correlations_FLP.c"
#include "../silk/float/residual_energy_FLP.c"
#include "../silk/float/warped_autocorrelation_FLP.c"
#include "../silk/float/wrappers_FLP.c"
#include "../silk/float/autocorrelation_FLP.c"
#include "../silk/float/burg_modified_FLP.c"
#include "../silk/float/bwexpander_FLP.c"
#include "../silk/float/energy_FLP.c"
#include "../silk/float/inner_product_FLP.c"
#include "../silk/float/k2a_FLP.c"
#include "../silk/float/LPC_inv_pred_gain_FLP.c"
#include "../silk/float/pitch_analysis_core_FLP.c"
#include "../silk/float/scale_copy_vector_FLP.c"
#include "../silk/float/scale_vector_FLP.c"
#include "../silk/float/schur_FLP.c"
#include "../silk/float/sort_FLP.c"
#endif

#undef PI

// CELT:

#include "../celt/bands.c"
#include "../celt/celt.c"
#include "../celt/celt_encoder.c"
#include "../celt/celt_decoder.c"
#include "../celt/cwrs.c"
#include "../celt/entcode.c"
#include "../celt/entdec.c"
#include "../celt/entenc.c"
#include "../celt/kiss_fft.c"
#include "../celt/laplace.c"
#include "../celt/mathops.c"
#include "../celt/mdct.c"
#include "../celt/modes.c"
#include "../celt/pitch.c"
#include "../celt/celt_lpc.c"
#include "../celt/quant_bands.c"
#include "../celt/rate.c"
#include "../celt/vq.c"

#if HAVE_X86
#include "../celt/x86/x86cpu.c"
#include "../celt/x86/x86_celt_map.c"
#include "../celt/x86/pitch_sse.c"

#include "../celt/x86/pitch_sse2.c"
#include "../celt/x86/vq_sse2.c"
#endif

#if HAVE_ARM
#include "../celt/arm/armcpu.c"
#include "../celt/arm/arm_celt_map.c"

// #include "../celt/arm/celt_pitch_xcorr_arm.s"
// #include "../celt/arm/armopts.s.in"

#include "../celt/arm/celt_neon_intr.c"
#include "../celt/arm/pitch_neon_intr.c"

#include "../celt/arm/celt_fft_ne10.c"
#include "../celt/arm/celt_mdct_ne10.c"
#endif

// OPUS:

#include "../src/opus.c"
#include "../src/opus_decoder.c"
#include "../src/opus_encoder.c"
#include "../src/opus_multistream.c"
#include "../src/opus_multistream_encoder.c"
#include "../src/opus_multistream_decoder.c"
#include "../src/repacketizer.c"
#include "../src/opus_projection_encoder.c"
#include "../src/opus_projection_decoder.c"
#include "../src/mapping_matrix.c"

#include "../src/analysis.c"
#include "../src/mlp.c"
#include "../src/mlp_data.c"

#endif /* COMPILE_SSE41_ONLY */
