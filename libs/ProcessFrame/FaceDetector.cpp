#include "FaceDetector.h"

FaceDetector::FaceDetector() {
    // Load the pre-trained Haar Cascade classifier for face detection
    if (!faceCascade.load("/media/beatriz/Dados/gitHub/Cpp-Training/haarcascade_frontalface_default.xml")) {
        throw std::runtime_error("Could not load Haar Cascade classifier");
    }
}

void FaceDetector::processFrame(cv::Mat& frame) {
    std::vector<cv::Rect> faces;

    // Detectar rostos na imagem colorida
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
    faceCascade.detectMultiScale(gray, faces, 1.1, 3, 0, cv::Size(30, 30));

    // Para cada rosto detectado
    for (const auto& face : faces) {
        // Extrair a região do rosto da imagem colorida
        cv::Mat faceROI_color = frame(face);

        // Extrair a mesma região da imagem em tons de cinza
        cv::Mat faceROI_gray = gray(face);

        // Converter a região cinza para BGR (3 canais) para poder copiar de volta
        cv::Mat faceROI_gray_bgr;
        cv::cvtColor(faceROI_gray, faceROI_gray_bgr, cv::COLOR_GRAY2BGR);

        // Substituir a região colorida pela versão em tons de cinza
        faceROI_gray_bgr.copyTo(faceROI_color);

        // Opcional: desenhar um retângulo ao redor do rosto
        cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
    }
}
