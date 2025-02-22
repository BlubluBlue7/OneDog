// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_RootLayer.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Engine/UserInterfaceSettings.h"

FVector2D GetDesignResolution()
{
	const UUserInterfaceSettings* UISettings = GetDefault<UUserInterfaceSettings>();
	if (UISettings)
	{
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		// 将浮点数四舍五入为整数
		int32 X = FMath::RoundToInt(ViewportSize.X);
		int32 Y = FMath::RoundToInt(ViewportSize.Y);

		// 返回 FIntPoint
		FIntPoint Size(X, Y);
		float Scale = UISettings->GetDPIScaleBasedOnSize(Size);
		// 获取设计分辨率
		return ViewportSize / Scale;
	}
	return FVector2D::ZeroVector; // 如果获取失败，返回默认值
}

void UUI_RootLayer::AddToRoot(UUI_UserWidgetBase* Layer)
{
	if(CurLayer)
	{
		LayerStack.Add(CurLayer);
		CurLayer->SetVisibility(ESlateVisibility::Hidden);
	}
	
	Layer->WidgetType = WIDGET_TYPE::LAYER;
	CurLayer = Layer;
	UCanvasPanelSlot* ChildSlot = RootPanel->AddChildToCanvas(Layer);
	if (ChildSlot)
	{
		// 获取视口分辨率
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		
		FVector2D Size = Layer->GetDesiredSize();
		FVector2D Size2 = GetDesiredSize();
		FVector2D DesignSize = GetDesignResolution();
		
		// 3. 设置子Widget的位置
		ChildSlot->SetPosition(FVector2D(0.0f, 0.0f)); // 设置位置 (X, Y)
		ChildSlot->SetSize(DesignSize);    // 设置大小 (Width, Height)
		ChildSlot->SetAnchors(FAnchors(0.5f, 0.5f));      // 设置锚点 (左上角)
		ChildSlot->SetAlignment(FVector2D(0.5f, 0.5f));   // 设置对齐方式
	}
}

void UUI_RootLayer::Close()
{
	if (CurLayer && LayerStack.Num() > 0)
	{
		CurLayer->RemoveFromParent();
		CurLayer = LayerStack.Pop();
		CurLayer->SetVisibility(ESlateVisibility::Visible);
	}
}

void UUI_RootLayer::CloseWindow(UUI_UserWidgetBase* Window)
{
	Window->RemoveFromParent();
}

void UUI_RootLayer::AddToModel(UUI_UserWidgetBase* Layer)
{
	Layer->WidgetType = WIDGET_TYPE::WINDOW;
	UCanvasPanelSlot* ChildSlot = ModelPanel->AddChildToCanvas(Layer);
	if (ChildSlot)
	{
		// 获取视口分辨率
		FVector2D ViewportSize;
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		
		FVector2D Size = Layer->GetDesiredSize();
		FVector2D Size2 = GetDesiredSize();
		FVector2D DesignSize = GetDesignResolution();
		
		// 3. 设置子Widget的位置
		ChildSlot->SetPosition(FVector2D(0.0f, 0.0f)); // 设置位置 (X, Y)
		// ChildSlot->SetSize(DesignSize);    // 设置大小 (Width, Height)
		ChildSlot->SetAnchors(FAnchors(0.5f, 0.5f));      // 设置锚点 (左上角)
		ChildSlot->SetAlignment(FVector2D(0.5f, 0.5f));   // 设置对齐方式
	}
}

void UUI_RootLayer::NativeConstruct()
{
	Super::NativeConstruct();

	// 延迟 0.1 秒后获取视口尺寸
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
	{
		FVector2D ViewportSize;
		if (GEngine && GEngine->GameViewport)
		{
			GEngine->GameViewport->GetViewportSize(ViewportSize);
			Text_Height->SetText(FText::FromString(FString::Printf(TEXT("高%f"), ViewportSize.Y)));
Text_Width->SetText(FText::FromString(FString::Printf(TEXT("宽%f"), ViewportSize.X)));
			UE_LOG(LogTemp, Log, TEXT("Viewport Size: %f x %f"), ViewportSize.X, ViewportSize.Y);
		}
	}, 0.1f, false); // 0.1 秒后执行

}