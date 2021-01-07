<GameProjectFile>
  <PropertyGroup Type="Node" Name="step4label" ID="46a11ecb-1dd2-45a1-a648-ed405c1fef33" Version="2.0.2.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="120" Speed="1.0000">
        <Timeline ActionTag="15866991" FrameType="ColorFrame">
          <ColorFrame FrameIndex="0" Alpha="0">
            <Color A="255" R="255" G="255" B="255" />
          </ColorFrame>
          <ColorFrame FrameIndex="30" Alpha="255">
            <Color A="255" R="255" G="255" B="255" />
          </ColorFrame>
          <ColorFrame FrameIndex="60" Alpha="0">
            <Color A="255" R="255" G="255" B="255" />
          </ColorFrame>
        </Timeline>
        <Timeline ActionTag="15866991" FrameType="ScaleFrame">
          <PointFrame FrameIndex="60" X="1.0000" Y="1.0000" />
        </Timeline>
        <Timeline ActionTag="15866991" FrameType="RotationSkewFrame">
          <PointFrame FrameIndex="60" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="138137983" FrameType="ColorFrame">
          <ColorFrame FrameIndex="60" Alpha="0">
            <Color A="255" R="255" G="255" B="255" />
          </ColorFrame>
          <ColorFrame FrameIndex="90" Alpha="255">
            <Color A="255" R="255" G="255" B="255" />
          </ColorFrame>
          <ColorFrame FrameIndex="120" Alpha="0">
            <Color A="255" R="255" G="255" B="255" />
          </ColorFrame>
        </Timeline>
        <Timeline ActionTag="597837477" FrameType="PositionFrame">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="120" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="597837477" FrameType="ScaleFrame">
          <PointFrame FrameIndex="0" X="1.0000" Y="1.0000" />
          <PointFrame FrameIndex="120" X="1.0000" Y="1.0000" />
        </Timeline>
        <Timeline ActionTag="597837477" FrameType="RotationSkewFrame">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000" />
          <PointFrame FrameIndex="120" X="0.0000" Y="0.0000" />
        </Timeline>
        <Timeline ActionTag="597837477" FrameType="EventFrame">
          <StringFrame FrameIndex="0" Value="" />
          <StringFrame FrameIndex="120" Value="end" />
        </Timeline>
      </Animation>
      <ObjectData Name="Node" CanEdit="False" FrameEvent="" ctype="SingleNodeObjectData">
        <Position X="0.0000" Y="0.0000" />
        <Scale ScaleX="1.0000" ScaleY="1.0000" />
        <AnchorPoint />
        <CColor A="255" R="255" G="255" B="255" />
        <Size X="0.0000" Y="0.0000" />
        <PrePosition X="0.0000" Y="0.0000" />
        <PreSize X="0.0000" Y="0.0000" />
        <Children>
          <NodeObjectData Name="Image_4" ActionTag="15866991" Alpha="0" FrameEvent="" Tag="145" ObjectIndex="4" Scale9Enable="True" LeftEage="100" RightEage="100" Scale9OriginX="100" Scale9Width="457" Scale9Height="140" ctype="ImageViewObjectData">
            <Position X="0.0000" Y="-400.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="1720.0000" Y="140.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="Text_4" ActionTag="-1559958059" FrameEvent="" Tag="146" ObjectIndex="4" PrePositionEnabled="True" FontSize="60" LabelText="把相同颜色的小笼女连成圈圈，圈内的小笼女也都会被抓到。" ctype="TextObjectData">
                <Position X="860.0000" Y="70.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="1620.0000" Y="60.0000" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.0000" Y="0.0000" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="pic/ui/anniu.png" />
          </NodeObjectData>
          <NodeObjectData Name="Image_6" ActionTag="138137983" Alpha="93" FrameEvent="" Tag="33" ObjectIndex="6" Scale9Enable="True" LeftEage="100" RightEage="100" Scale9OriginX="100" Scale9Width="457" Scale9Height="140" ctype="ImageViewObjectData">
            <Position X="0.0000" Y="-400.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="1020.0000" Y="140.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
            <Children>
              <NodeObjectData Name="Text_6" ActionTag="1093031166" FrameEvent="" Tag="34" ObjectIndex="6" PrePositionEnabled="True" FontSize="60" LabelText="看明白了吗？自己试试画个圈吧！" ctype="TextObjectData">
                <Position X="510.0000" Y="70.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <CColor A="255" R="255" G="255" B="255" />
                <Size X="900.0000" Y="60.0000" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.0000" Y="0.0000" />
              </NodeObjectData>
            </Children>
            <FileData Type="Normal" Path="pic/ui/anniu.png" />
          </NodeObjectData>
          <NodeObjectData Name="event" ActionTag="597837477" FrameEvent="" Tag="54" ObjectIndex="1" IconVisible="True" ctype="SingleNodeObjectData">
            <Position X="0.0000" Y="0.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <AnchorPoint />
            <CColor A="255" R="255" G="255" B="255" />
            <Size X="0.0000" Y="0.0000" />
            <PrePosition X="0.0000" Y="0.0000" />
            <PreSize X="0.0000" Y="0.0000" />
          </NodeObjectData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameProjectFile>