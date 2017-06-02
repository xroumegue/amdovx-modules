/*
Copyright (c) Xavier Roumegue

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include"publishkernels.h"

/************************************************************************************************************
input parameter validator.
param [in] node The handle to the node.
param [in] index The index of the parameter to validate.
*************************************************************************************************************/
static vx_status VX_CALLBACK CV_houghLinesP_InputValidator(vx_node node, vx_uint32 index)
{
	vx_status status = VX_SUCCESS ;
	vx_parameter param = vxGetParameterByIndex(node, index);

	if (index == 0) {
		vx_image image;
		vx_df_image df_image = VX_DF_IMAGE_VIRT;
		STATUS_ERROR_CHECK(vxQueryParameter(param, VX_PARAMETER_ATTRIBUTE_REF, &image, sizeof(vx_image)));
		STATUS_ERROR_CHECK(vxQueryImage(image, VX_IMAGE_ATTRIBUTE_FORMAT, &df_image, sizeof(df_image)));
		if (df_image != VX_DF_IMAGE_U8)
			status = VX_ERROR_INVALID_VALUE;
		vxReleaseImage(&image);
	} else if (index == 1) {
		vx_array array; vx_size size = 0;
		STATUS_ERROR_CHECK(vxQueryParameter(param, VX_PARAMETER_ATTRIBUTE_REF, &array, sizeof(array)));
		STATUS_ERROR_CHECK(vxQueryArray(array, VX_ARRAY_ATTRIBUTE_CAPACITY, &size, sizeof(size)));
		vxReleaseArray(&array);

	} else if (index == 2) {
		vx_scalar scalar = 0; vx_enum type = 0;	vx_float32 value = 0;
		STATUS_ERROR_CHECK(vxQueryParameter(param, VX_PARAMETER_ATTRIBUTE_REF, &scalar, sizeof(scalar)));
		STATUS_ERROR_CHECK(vxQueryScalar(scalar, VX_SCALAR_ATTRIBUTE_TYPE, &type, sizeof(type)));
		STATUS_ERROR_CHECK(vxReadScalarValue(scalar, &value));
		if (value < 0 || type !=  VX_TYPE_FLOAT32)
			status = VX_ERROR_INVALID_VALUE;
		vxReleaseScalar(&scalar);
	} else if (index == 3) {
		vx_scalar scalar = 0; vx_enum type = 0;	vx_float32 value = 0;
		STATUS_ERROR_CHECK(vxQueryParameter(param, VX_PARAMETER_ATTRIBUTE_REF, &scalar, sizeof(scalar)));
		STATUS_ERROR_CHECK(vxQueryScalar(scalar, VX_SCALAR_ATTRIBUTE_TYPE, &type, sizeof(type)));
		STATUS_ERROR_CHECK(vxReadScalarValue(scalar, &value));
		if (value < 0 || type != VX_TYPE_FLOAT32)
			status = VX_ERROR_INVALID_VALUE;
		vxReleaseScalar(&scalar);
	} else if (index == 4) {
		vx_scalar scalar = 0; vx_enum type = 0;	vx_int32 value = 0;
		STATUS_ERROR_CHECK(vxQueryParameter(param, VX_PARAMETER_ATTRIBUTE_REF, &scalar, sizeof(scalar)));
		STATUS_ERROR_CHECK(vxQueryScalar(scalar, VX_SCALAR_ATTRIBUTE_TYPE, &type, sizeof(type)));
		STATUS_ERROR_CHECK(vxReadScalarValue(scalar, &value));
		if (value < 0 || type != VX_TYPE_INT32)
			status = VX_ERROR_INVALID_VALUE;
		vxReleaseScalar(&scalar);

	} else if (index == 5) {
		vx_scalar scalar = 0; vx_enum type = 0;	vx_float32 value = 0;
		STATUS_ERROR_CHECK(vxQueryParameter(param, VX_PARAMETER_ATTRIBUTE_REF, &scalar, sizeof(scalar)));
		STATUS_ERROR_CHECK(vxQueryScalar(scalar, VX_SCALAR_ATTRIBUTE_TYPE, &type, sizeof(type)));
		STATUS_ERROR_CHECK(vxReadScalarValue(scalar, &value));
		if (value < 0 || type != VX_TYPE_FLOAT32)
			status = VX_ERROR_INVALID_VALUE;
		vxReleaseScalar(&scalar);

	} else if (index == 6) {
		vx_scalar scalar = 0; vx_enum type = 0;	vx_float32 value = 0;
		STATUS_ERROR_CHECK(vxQueryParameter(param, VX_PARAMETER_ATTRIBUTE_REF, &scalar, sizeof(scalar)));
		STATUS_ERROR_CHECK(vxQueryScalar(scalar, VX_SCALAR_ATTRIBUTE_TYPE, &type, sizeof(type)));
		STATUS_ERROR_CHECK(vxReadScalarValue(scalar, &value));
		if (value < 0 || type != VX_TYPE_FLOAT32)
			status = VX_ERROR_INVALID_VALUE;
		vxReleaseScalar(&scalar);
	}

	vxReleaseParameter(&param);

	return status;
}

/************************************************************************************************************
output parameter validator.
*************************************************************************************************************/
static vx_status VX_CALLBACK CV_houghLinesP_OutputValidator(vx_node node, vx_uint32 index, vx_meta_format meta)
{
	vx_status status = VX_SUCCESS ;
	if (index == 1) {
		vx_parameter output_param = vxGetParameterByIndex(node, 1);
		vx_array output; vx_size size = 0; vx_enum type;

		STATUS_ERROR_CHECK(vxQueryParameter(output_param, VX_PARAMETER_ATTRIBUTE_REF, &output, sizeof(vx_array)));
		STATUS_ERROR_CHECK(vxQueryArray(output, VX_ARRAY_ATTRIBUTE_CAPACITY, &size, sizeof(size)));
		STATUS_ERROR_CHECK(vxQueryArray(output, VX_ARRAY_ATTRIBUTE_ITEMTYPE, &type, sizeof(type)));


		if (size <= 0)
			status = VX_ERROR_INVALID_VALUE;

		if (type != VX_TYPE_RECTANGLE)
			status = VX_ERROR_INVALID_TYPE;

		vxReleaseArray(&output);
		vxReleaseParameter(&output_param);

		STATUS_ERROR_CHECK(vxSetMetaFormatAttribute(meta, VX_ARRAY_ATTRIBUTE_CAPACITY, &size, sizeof(size)));
		STATUS_ERROR_CHECK(vxSetMetaFormatAttribute(meta, VX_ARRAY_ATTRIBUTE_ITEMTYPE, &type, sizeof(type)));
	} else if (index == 7) {
		vx_parameter output_param = vxGetParameterByIndex(node, 7);
		vx_enum type;
		vx_scalar out;
		STATUS_ERROR_CHECK(vxQueryParameter(output_param, VX_PARAMETER_ATTRIBUTE_REF, &out, sizeof(vx_scalar)));
		vxQueryScalar(out, VX_SCALAR_ATTRIBUTE_TYPE, &type, sizeof(type));
		if (type != VX_TYPE_INT32)
			status = VX_ERROR_INVALID_TYPE;

		vxReleaseParameter(&output_param);
		STATUS_ERROR_CHECK(vxSetMetaFormatAttribute(meta, VX_SCALAR_ATTRIBUTE_TYPE, &type, sizeof(type)));
	}

	return status;
}

/************************************************************************************************************
Execution Kernel
*************************************************************************************************************/
static vx_status VX_CALLBACK CV_houghLinesP_Kernel(vx_node node, const vx_reference *parameters, vx_uint32 num)
{
	vx_status status = VX_SUCCESS;

	Mat *mat;
	int threshold;
	float rho, theta, minLineLength, maxLineGap;
	vx_int32 value = 0;
	vx_float32 value_f = 0;
	vx_image  image = (vx_image) parameters[0];
	vx_array  lines = (vx_array) parameters[1];
	vx_scalar RHO = (vx_scalar) parameters[2];
	vx_scalar THETA = (vx_scalar) parameters[3];
	vx_scalar THRESHOLD = (vx_scalar) parameters[4];
	vx_scalar MINLINELENGTH = (vx_scalar) parameters[5];
	vx_scalar MAXLINEGAP = (vx_scalar) parameters[6];
	vx_scalar num_lines= (vx_scalar) parameters[7];

	//Extracting Values from the Scalar
	STATUS_ERROR_CHECK(vxReadScalarValue(RHO, &value_f));
	rho = value_f;
	STATUS_ERROR_CHECK(vxReadScalarValue(THETA, &value_f));
	theta = value_f;
	STATUS_ERROR_CHECK(vxReadScalarValue(THRESHOLD, &value));
	threshold = value;
	STATUS_ERROR_CHECK(vxReadScalarValue(MINLINELENGTH, &value_f));
	minLineLength = value_f;
	STATUS_ERROR_CHECK(vxReadScalarValue(MAXLINEGAP, &value_f));
	maxLineGap = value_f;

	//Converting VX Image to OpenCV Mat
	STATUS_ERROR_CHECK(VX_to_CV_Image(&mat, image));

	//Compute using OpenCV
	vector<Vec4i> _lines;
	cv::HoughLinesP(*mat, _lines, rho, theta,
			threshold, minLineLength, maxLineGap);

	STATUS_ERROR_CHECK(CV_to_VX_lines(_lines, lines));
	value = _lines.size();
	STATUS_ERROR_CHECK(vxWriteScalarValue(num_lines, &value));

	vxAddLogEntry((vx_reference) node, VX_FAILURE, "%s: %d: %x lines extracted\n", __func__, __LINE__, value);
	return status;
}

/************************************************************************************************************
Function to Register the Kernel for Publish
*************************************************************************************************************/
vx_status CV_houghLinesP_Register(vx_context context)
{
	vx_status status = VX_SUCCESS;
	vx_kernel Kernel = vxAddKernel(context,
		"org.opencv.houghlinesp",
		VX_KERNEL_EXT_CV_HOUGHLINESP,
		CV_houghLinesP_Kernel,
		8,
		CV_houghLinesP_InputValidator,
		CV_houghLinesP_OutputValidator,
		nullptr,
		nullptr);

	if (Kernel) {
		PARAM_ERROR_CHECK(vxAddParameterToKernel(Kernel, 0, VX_INPUT, VX_TYPE_IMAGE, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(Kernel, 1, VX_BIDIRECTIONAL, VX_TYPE_ARRAY, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(Kernel, 2, VX_INPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(Kernel, 3, VX_INPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(Kernel, 4, VX_INPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(Kernel, 5, VX_INPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_OPTIONAL));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(Kernel, 6, VX_INPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_OPTIONAL));
		PARAM_ERROR_CHECK(vxAddParameterToKernel(Kernel, 7, VX_OUTPUT, VX_TYPE_SCALAR, VX_PARAMETER_STATE_REQUIRED));
		PARAM_ERROR_CHECK(vxFinalizeKernel(Kernel));
	}

	if (status != VX_SUCCESS){
exit:		vxRemoveKernel(Kernel);
		return VX_FAILURE;
	}

	return status;
}
